/*!
\file       SequentialScheduler.cpp
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version    0.1
\date       01/04/2016
\brief      Sequential scheduler definition class
\remarks    none
*/
#include "SequentialScheduler.h"

using namespace boost::interprocess;


SequentialScheduler::SequentialScheduler(const std::string &queue_name, const std::string &filename, int ncores) :
        Scheduler{filename, ncores}, filename{filename}, queue_name{queue_name} {

}

SequentialScheduler::~SequentialScheduler() {

}


int SequentialScheduler::get_unloaded_core(const std::vector<double> &cores_load) {
    for (unsigned i = 0; i < cores_load.size(); ++i)
        if (cores_load[i] == 0) return i;
    return -1;
}

int SequentialScheduler::get_less_loaded_core(const std::vector<double> &cores_load) {
    int min = 0;
    for (unsigned i = 0; i < cores_load.size(); ++i)
        if (cores_load[i] < cores_load[min]) min = i;
    return min;
}

bool SequentialScheduler::exist_suitable_core(const std::vector<double> &cores_load, double task_load) {
    for (unsigned i = 0; i < cores_load.size(); ++i) {
        if (cores_load[i] + task_load <= 1.0) {
            return true;
        }
    }
    return false;
}

void SequentialScheduler::get_cores_load(const VectorTasks &process_list, std::vector<double> &cores_load) {
    for (auto const &process : process_list)
        cores_load[process.num_cpu] += process.load;
}

int SequentialScheduler::get_core_to_assign(const VectorTasks &process_list, double task_load) {
    int core = -1;
    initCores();

    get_cores_load(process_list, cores_load);
    print_cores_load(file_logs, cores_load);

    if (exist_suitable_core(cores_load, task_load)) {
        print_searching_unloaded_core(file_logs);

        /* Strategy : in "readme.md" */
        core = get_unloaded_core(cores_load);
        if (core == -1) {
            print_no_unloaded_core_found(file_logs);
            core = get_less_loaded_core(cores_load);
        }
    }
    return core;
}


void SequentialScheduler::start() {

    std::cout << "Launching scheduler in sequential mode..." << std::endl;

    /* Variables */
    pid_t pid;
    int core, status;
    cpu_set_t set;
    task task_res;
    unsigned int priority;
    message_queue::size_type rcv_size;

    // Sigaction variable to make sure childs are not zombified
    struct sigaction sigchld_action;
    sigchld_action.sa_handler = SIG_DFL;
    sigchld_action.sa_flags = SA_NOCLDWAIT;

    // ptime variable to timeout processes and measures exec time
    boost::posix_time::ptime start;
    boost::posix_time::ptime timeout;
    using clock = boost::posix_time::microsec_clock;

    /* Shared memory building */
    // Delete if exists
    shared_memory_object::remove("Sched_shm");
    // Create a new segment with given name and size
    managed_shared_memory segment(create_only, "Sched_shm", 65536);
    // Initialize shared memory STL-compatible allocator
    const ShmemAllocator alloc_inst(segment.get_segment_manager());
    // Construct a vector named "VectorTasks" in shared memory using the previous allocator
    VectorTasks *process_list = segment.construct<VectorTasks>("VectorTasks")(alloc_inst);


    /* Mutex creation */
    // Delete if exists
    named_mutex::remove("VectorTasks_mutex");
    // Create the named mutex
    named_mutex mutex(create_only, "VectorTasks_mutex");

    /* Open message queue */
    message_queue queue(open_or_create, queue_name.c_str(), 1000, sizeof(task));

    file_lock f_lock(filename.c_str());

    // Defining a timeout for the scheduler
    timeout = clock::local_time() + boost::posix_time::minutes(1);

    while (clock::local_time() < timeout) {
        if (queue.try_receive(&task_res, sizeof(task), rcv_size, priority)) {
            // Reseting timeout and start time to endure task supposed duration and compute real exec duration
            timeout = clock::local_time() + boost::posix_time::seconds(task_res.timeout + 60);
            start = clock::local_time();

            // Reseting set of CPUs for sched affinity
            CPU_ZERO(&set);

            // Create a new task with the specs received from the message queue
            task _task = task_res;

            // Write into logs (secured by scoped file_lock for interprocess)
            {
                scoped_lock<file_lock> fs_lock(f_lock);
                print_process_incoming(file_logs, _task);
            }



            // Choose the cpu
            core = get_core_to_assign(*process_list, _task.load);
            // If there's not a cpu which can handle the task...
            while (core == -1) {
                {
                    scoped_lock<file_lock> fs_lock(f_lock);
                    print_no_core_available(file_logs);
                }
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
                    {
                        scoped_lock<file_lock> fs_lock(f_lock);
                        print_set_affinity_error(file_logs);
                    }
                    exit(ERROR_SCHED_AFFINITY);
                } else {
                    std::string command = task_res.command;

                    // Executing the task, and a watchdog to kill if timeout
                    pid_t exec = fork();

                    // Process that contains the command
                    if (exec == 0) {
                        setpgid(getpid(), getpid());
                        if (std::system(command.c_str())) {
                            boost::posix_time::time_duration duration =
                                    boost::posix_time::second_clock::local_time() - start;
                            // Tell how good was that ephemeral life...
                            {
                                scoped_lock<file_lock> fs_lock(f_lock);
                                print_process_handled(file_logs, _task, getppid(), core, duration.total_milliseconds());
                            }
                            exit(EXIT_SUCCESS);
                        }
                    } else {
                        sleep(_task.timeout);
                        pid_t result = waitpid(exec, &status, WNOHANG);
                        // If his child is still alive...
                        if (result == 0) {
                            // Kill the process because the timeout is exceeded
                            kill(-exec, SIGTERM);
                            {
                                scoped_lock<file_lock> fs_lock(f_lock);
                                print_process_killed_timeout(file_logs, getpid(), _task);
                            }
                        }
                    }

                    //Open the managed segment
                    managed_shared_memory segment(open_only, "Sched_shm");

                    // Find the vector using the name
                    VectorTasks *process_list = segment.find<VectorTasks>("VectorTasks").first;

                    {
                        scoped_lock<named_mutex> lock(mutex);
                        // Remove it from the list
                        process_list->erase(std::remove(process_list->begin(), process_list->end(), _task),
                                            process_list->end());
                    }

                }
                exit(EXIT_SUCCESS);
                // Parent's exec
            } else {
                // Tell where the process has been dispatched
                {
                    scoped_lock<file_lock> fs_lock(f_lock);
                    print_process_sent(file_logs, pid, core);
                }
            }
            // Make sure children are not zombies
            sigaction(SIGCHLD, &sigchld_action, NULL);
        }
    }

    // Destruct shared memories
    named_mutex::remove("VectorTasks_mutex");
    shared_memory_object::remove("Sched_shm");
}


