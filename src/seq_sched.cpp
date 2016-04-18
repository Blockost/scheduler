#include "seq_sched.h"





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

int get_unloaded_core(const int cores_load[4]){
    for(int i = 0; i < 4; ++i)
        if(cores_load[i] == 0) return i;
    return -1;
}

void get_cores_load(const VectorTasks &process_list, int* cores_load){
    for(auto const &process : process_list)
        cores_load[process.num_cpu] += process.load;
}

int get_core_to_assign(const VectorTasks &process_list){
    int core = 0;
    int cores_load[4] = {0,0,0,0};

    get_cores_load(process_list, cores_load);
    std::cout << "cpu0: " << cores_load[0]
    << "; cpu1: " << cores_load[1]
    << "; cpu2: " << cores_load[2]
    << "; cpu3: " << cores_load[3]
    << std::endl;

    /* Strategy : in "readme.md" */
    std::cout << termcolor::red << "Searching for an unloaded core..." << std::endl;
    core = get_unloaded_core(cores_load);
    if(core == -1){
        std::cout << "Not found !" << std::endl;
        std::cout << termcolor::green << "Searching for a core that can fit the task... //TODO" << termcolor::reset << std::endl;
        //TODO Take the (strategy ?) core which best fits the process' hosting procedure
        core = 0;
    }

    return core;
}

// TODO A voir si on ne devrait pas garder les process dans la liste et ajouter un champs "done" à la structure plutôt !
//process_list.erase(remove(process_list.begin(), process_list.end(), _task), process_list.end());


void launch_sequential(const char* filename){

    std::cout << "Launching scheduler in sequential mode..." << std::endl;

    // Delete if exists
    shared_memory_object::remove("MySharedMemory");

    ///Create a new segment with given name and size
    managed_shared_memory segment(create_only, "MySharedMemory", 65536);

    //Initialize shared memory STL-compatible allocator
    const ShmemAllocator alloc_inst (segment.get_segment_manager());

    //Construct a vector named "VectorTasks" in shared memory with argument alloc_inst
    VectorTasks *process_list = segment.construct<VectorTasks>("VectorTasks")(alloc_inst);



    int q_id = msgget(ftok(filename, 0), 0);
    pid_t pid;
    int core;
    cpu_set_t set;
    task task_res;




    while(1){
        if(msgrcv(q_id, &task_res, 100, 1, 0) != -1) {
            CPU_ZERO(&set);

            // Create a new task with the specs received from the message queue
            task _task = task_res;
            std::cout << termcolor::blue << termcolor::on_white << "------------------------------------"
                << termcolor::reset << std::endl;
            std::cout << "New task arrived :" << _task << std::endl;

            // Choose the cpu
            core = get_core_to_assign(*process_list);
            CPU_SET(core, &set);
            _task.num_cpu = core;

            // Create a new process which will host the task execution
            pid = fork();
            switch(pid) {

                // Child's exec
                case 0:
                    {
                        if (sched_setaffinity(getpid(), sizeof(set), &set) == -1) {
                            std::cout << termcolor::red << termcolor::on_white << "SET_AFFINITY_ERROR"
                                << termcolor::reset << std::endl;
                            exit(ERROR_SCHED_AFFINITY);
                        }else{
                            //Open the managed segment
                            managed_shared_memory segment(open_only, "MySharedMemory");

                            //Find the vector using the c-string name
                            VectorTasks *process_list = segment.find<VectorTasks>("VectorTasks").first;

                            // Add the task to the list of processes
                            process_list->push_back(_task);

                            // Simulate the time taken by the processus
                            //TODO Ajouter une méthod exec() dans la tâche à la place du sleep() ?
                            sleep(_task.duration);

                            // Remove it from the list
                            process_list->erase(std::remove(process_list->begin(), process_list->end(), _task), process_list->end());

                            // Tell how good was that ephemeral life...
                            print_process_handled(_task, core);
                        }


                    }
                    break;

                // Parent's exec
                default:
                    // Tell where the process has been dispatched
                    print_process_sent(pid, core);
                    break;
            }
        }

        //TODO Regarder ce que ça fait !!
        /*else{
            sort(process_list.begin(),process_list.end(),less_than_key());
            for (unsigned j = 0; j < process_list.size(); ++j) {
                std::cout << "Process handled : "
                << process_list.at(j).duration
                << " | " <<  process_list.at(j).load << "  |  prio :" <<  process_list.at(j).priority
                << std::endl;
            }
        }*/
    }
}
