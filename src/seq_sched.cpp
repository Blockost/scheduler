#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include "seq_sched.h"
#include "util/util.h"
#include <sys/wait.h>

int get_unloaded_core(const double cores_load[4]){
    for(unsigned i = 0; i < 4; ++i)
        if(cores_load[i] == 0) return i;
    return -1;
}

int get_less_loaded_core(const double cores_load[4]){
    int min = 0;
    for(unsigned i = 0; i < 4; ++i)
        if(cores_load[i] < min) min = i;
    return min;
}

bool exist_suitable_core(const double cores_load[4], double task_load){
    for(unsigned i = 0; i < 4; ++i) {
        if (cores_load[i]+task_load <= 1.0){
            return true;
        }
    }
    return false;
}

void get_cores_load(const VectorTasks &process_list, double* cores_load){
    for(auto const &process : process_list)
        cores_load[process.num_cpu] += process.load;
}

int get_core_to_assign(const VectorTasks &process_list, double task_load){
    int core = -1;
    double cores_load[4] = {0,0,0,0};

    get_cores_load(process_list, cores_load);
    print_cores_load(cores_load);

    if(exist_suitable_core(cores_load, task_load)) {
        /* Strategy : in "readme.md" */
        print_searching_unloaded_core();
        core = get_unloaded_core(cores_load);
        if (core == -1) {
            print_no_unloaded_core_found();
            core = get_less_loaded_core(cores_load);
        }
    }
    return core;
}


void launch_sequential(){

    std::cout << "Launching scheduler in sequential mode..." << std::endl;

    /* Variables */
    pid_t pid;
    int core;
    cpu_set_t set;
    task task_res;
    unsigned int priority;
    message_queue::size_type rcv_size;
    std::stringstream ss;
    // Sigaction variable to make sure childs are not zombified
    struct sigaction sigchld_action;
    sigchld_action.sa_handler = SIG_DFL;
    sigchld_action.sa_flags = SA_NOCLDWAIT;
    // ptime variable to timeout processes and measures exec time
    boost::posix_time::ptime start;
    boost::posix_time::ptime timeout;
    using clock = boost::posix_time::second_clock;


    /* Shared memory building */
    // Delete if exists
    shared_memory_object::remove("MySharedMemory");
    // Create a new segment with given name and size
    managed_shared_memory segment(create_only, "MySharedMemory", 65536);
    // Initialize shared memory STL-compatible allocator
    const ShmemAllocator alloc_inst (segment.get_segment_manager());
    // Construct a vector named "VectorTasks" in shared memory using the previous allocator
    VectorTasks *process_list = segment.construct<VectorTasks>("VectorTasks")(alloc_inst);

    /* Mutex creation */
    // Delete if exists
    named_mutex::remove("VectorTasks_mutex");
    // Create the named mutex
    named_mutex mutex(create_only, "VectorTasks_mutex");

    /* Open message queue */
    message_queue queue(open_or_create, "scheduler_queue", 1000, sizeof(task));

    /* Open or create file for logging */
    std::fstream file_logs("logs", std::fstream::out | std::fstream::app);
    if(file_logs){
        file_logs.close();
        std::remove("logs");
    }

    file_logs.open("logs", std::fstream::out | std::fstream::app);

    /* Create a lock for interprocess synchro */
    file_lock f_lock;

    /*if(file_logs){
        file_lock f_lock("logs");
    }*/

    file_logs.close();

    // Defining a timeout for the scheduler
    timeout = clock::local_time() + boost::posix_time::minutes(1);

    while(clock::local_time() < timeout) {
        if(queue.try_receive(&task_res, sizeof(task), rcv_size, priority)) {
            // Reseting timeout and start time to endure task supposed duration and compute real exec duration
            timeout = clock::local_time() + boost::posix_time::seconds(task_res.timeout + 60);
            start = clock::local_time();

            // Reseting set of CPUs for sched affinity
            CPU_ZERO(&set);

            // Create a new task with the specs received from the message queue
            task _task = task_res;
            print_process_incoming(_task);

            //TODO File locks make the program crash... All logging disabled for the moment !
            /*// Write into logs (secured by file_lock for interprocess)
            if(file_logs){
                ss << "**** New task arrived : "
                    << _task << " ****" << std::endl;
                file_logs << ss.str();
                file_logs.flush();
                ss.flush();
                scoped_lock<file_lock> fs_lock(f_lock);
                //write_into_stream(file_logs, ss);
            }*/


            // Choose the cpu
            core = get_core_to_assign(*process_list, _task.load);
            // If there's not a cpu which can handle the task...
            while (core == -1) {
                print_no_core_available();
                /*if(file_logs){
                    ss << "No core available for the moment..." << std::endl;
                    scoped_lock<file_lock> fs_lock(f_lock);
                    write_into_stream(file_logs, ss);
                }*/
                // Wait for it...
                sleep(1);
                // And repeat...
                core = get_core_to_assign(*process_list, _task.load);
            }

            CPU_SET(core, &set);
            _task.num_cpu = core;

            // Define a scope
            {
                // Try to lock the mutex
                scoped_lock<named_mutex> lock(mutex);
                // Add the task to the list of processes
                process_list->push_back(_task);
                // Mutex will be unlocked at the end of the scope, no matter what happens
            }

            // Create a new process which will host the task execution
            pid = fork();
            if (pid == 0) {
                if (sched_setaffinity(getpid(), sizeof(set), &set) == -1) {
                    print_set_affinity_error();
                    exit(ERROR_SCHED_AFFINITY);
                } else {
                    std::string command = task_res.command;

                    // Executing the task, and a watchdog to kill if timeout
                    pid_t exec = fork();

                    // Process that contains the command
                    if (exec == 0) {
                        setpgid(getpid(), getpid());
                        std::system(command.c_str());
                        // Tell how good was that ephemeral life...
                        boost::posix_time::time_duration duration = boost::posix_time::second_clock::local_time() - start;
                        print_process_handled(_task, getppid(), core, duration.total_milliseconds());
                        exit(EXIT_SUCCESS);
                    } else {
                        sleep(_task.timeout);
                        int status;
                        pid_t result = waitpid(exec, &status, WNOHANG);
                        // If his child is still alive...
                        if (result == 0) {
                            // Kill the process because the timeout is exceeded
                            kill(-exec, SIGTERM);
                            print_process_killed_timeout(_task, getpid());
                        }
                    }

                    //Open the managed segment
                    managed_shared_memory segment(open_only, "MySharedMemory");

                    // Find the vector using the c-string name
                    VectorTasks *process_list = segment.find<VectorTasks>("VectorTasks").first;

                    {
                        scoped_lock<named_mutex> lock(mutex);
                        // Remove it from the list
                        process_list->erase(std::remove(process_list->begin(), process_list->end(), _task),
                                            process_list->end());
                    }

                    /*if(file_logs){
                        ss << "Process handled : "
                        << _task.timeout << "s"
                        << " for " << _task.load << "CPU"
                        << " by PID " << getpid()
                        << " on core" << core << std::endl;
                        scoped_lock<file_lock> fs_lock(f_lock);
                        write_into_stream(file_logs, ss);
                    }*/
                }
                // TODO Check htop -> Les processus pères restent même après l'exit
                exit(EXIT_SUCCESS);
            // Parent's exec
            } else {
                // Tell where the process has been dispatched
                print_process_sent(pid, core);
            }
            // Make sure childs are not zombies
            sigaction(SIGCHLD, &sigchld_action, NULL);
        }
    }
}
