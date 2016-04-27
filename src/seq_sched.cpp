#include "seq_sched.h"
#include <boost/interprocess/sync/named_mutex.hpp>
#include <sys/wait.h>

void print_process_handled(task _task, int core) {
    std::cout << "Process handled : "
    << _task.duration << "s"
    << " for " << _task.load << "CPU"
    << " by " << termcolor::green << "PID " << getpid() << termcolor::reset
    << " on " << termcolor::red << "core" << core
    << termcolor::reset << std::endl;
}

void print_process_sent(int pid, int core) {
    std::cout << "Process delivered to PID " << pid
    << " on " << termcolor::red << "core" << core
    << termcolor::reset << std::endl;
}

void print_cores_load(const float cores_load[4]){
    for(unsigned i = 0; i < 4; ++i) {
        std::cout << "cpu" << i << ": "
            << cores_load[i] << "; ";
    }
    std::cout << std::endl;
}

int get_unloaded_core(const float cores_load[4]){
    for(unsigned i = 0; i < 4; ++i)
        if(cores_load[i] == 0) return i;
    return -1;
}

int get_less_loaded_core(const float cores_load[4]){
    float min = 0;
    for(unsigned i = 0; i < 4; ++i)
        if(cores_load[i] < min) min = i;
    return min;
}

bool exist_suitable_core(const float cores_load[4], float task_load){
    for(unsigned i = 0; i < 4; ++i)
        if(cores_load[i] + task_load <= 1.0) return true;
    return false;
}

void get_cores_load(const VectorTasks &process_list, float* cores_load){
    for(auto const &process : process_list)
        cores_load[process.num_cpu] += process.load;
}

int get_core_to_assign(const VectorTasks &process_list, float task_load){
    int core = 0;
    float cores_load[4] = {0,0,0,0};

    do{
        get_cores_load(process_list, cores_load);
        //print_cores_load(cores_load);
        //TODO Sleep(1) ?
    }while(!exist_suitable_core(cores_load, task_load));


    /* Strategy : in "readme.md" */
    std::cout << termcolor::red << "Searching for an unloaded core..." << termcolor::reset << std::endl;
    core = get_unloaded_core(cores_load);
    if(core == -1){
        std::cout << termcolor::red << "Not found !" << termcolor::reset << std::endl;
        std::cout << termcolor::green << "Searching for a core that can fit the task..." << termcolor::reset << std::endl;
        core = get_less_loaded_core(cores_load);
    }
    return core;
}


void launch_sequential(){

    std::cout << "Launching scheduler in sequential mode..." << std::endl;

    pid_t pid;
    int core;
    cpu_set_t set;
    task task_res;

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


    message_queue queue(open_or_create, "scheduler_queue", 1000, sizeof(task));

    unsigned int priority;
    message_queue::size_type rcv_size;


    while(1){
        if(queue.try_receive(&task_res, 100, rcv_size, priority)) {
            CPU_ZERO(&set);

            // Create a new task with the specs received from the message queue
            task _task = task_res;
            std::cout << termcolor::blue << termcolor::on_white
                << "------------------------------------"
                << termcolor::reset << std::endl;
            std::cout << "New task arrived :" << _task << std::endl;

            // Choose the cpu
            core = get_core_to_assign(*process_list, _task.load);
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
                {
                    if (sched_setaffinity(getpid(), sizeof(set), &set) == -1) {
                        std::cout << termcolor::red << termcolor::on_white << "SET_AFFINITY_ERROR"
                        << termcolor::reset << std::endl;
                        exit(ERROR_SCHED_AFFINITY);
                    }else{
                        // TODO: replace with command passed by the user
                        std::string command = "sleep 5 && echo 'coucou'";

                        // Executing the task, and a watchdog to kill if timeout
                        pid_t exec = fork();
                        if (exec == 0) {
                            setpgid(getpid(), getpid());
                            std::system(command.c_str());
                            // Tell how good was that ephemeral life...
                            print_process_handled(_task, core);
                            exit(EXIT_SUCCESS);
                        } else {
                            sleep(_task.duration);
                            int status;
                            // TODO
                            pid_t result = waitpid(exec, &status, WNOHANG);
                            if (result == 0) {
                                // Kill process if timeout
                                kill(-exec, SIGTERM);
                                std::cout << termcolor::red << "Process " << exec << " killed after " << _task.duration << "s of execution" << termcolor::reset << std::endl;
                            }
                            //Open the managed segment
                            managed_shared_memory segment(open_only, "MySharedMemory");

                            // Find the vector using the c-string name
                            VectorTasks *process_list = segment.find<VectorTasks>("VectorTasks").first;

                            {
                                scoped_lock<named_mutex> lock(mutex);
                                // Remove it from the list
                                process_list->erase(std::remove(process_list->begin(), process_list->end(), _task), process_list->end());
                            }
                        }
                    }
                }
                exit(EXIT_SUCCESS);
            } else {
                // Tell where the process has been dispatched
                print_process_sent(pid, core);
            }
        }
    }
}
