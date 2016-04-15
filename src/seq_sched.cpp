#include "seq_sched.h"


void print_process_handled(task _task, int core) {
    cout << "Process handled : "
    << _task.duration << "s"
    << " for " << _task.load << "CPU"
    << " by " << termcolor::green << "PID " << getpid()
    << " on " << termcolor::red << "core" << core
    << termcolor::reset << endl;
}

void print_process_sent(int pid, int core) {
    cout << "Process delivered to PID " << pid
    << " on " << termcolor::red << "core" << core
    << termcolor::reset << endl;
}

int get_unloaded_core(const vector<task> process_list) {
    bool arr_bool[4];
    for(auto const &process : process_list){
        if(arr_bool[process.num_cpu])
            arr_bool[process.num_cpu] = true;
    }

    for(int i = 0; i < 4; i++){
        if(!arr_bool[i]) return i;
    }
    return -1;
}

float get_core_load(const vector<task> process_list, int num_cpu){
    float load = 0;
    for(auto const &process : process_list){
        if(process.num_cpu == num_cpu)
            load += process.load;
    }
    return load;
}

int get_core_to_assign(const vector<task> process_list){
    int core;

    cout << "cpu0: " << get_core_load(process_list, 0)
    << "; cpu1: " << get_core_load(process_list, 1)
    << "; cpu2: " << get_core_load(process_list, 2)
    << "; cpu3: " << get_core_load(process_list, 3)
    << endl;

    cout << termcolor::red << "Searching for an auloaded core..." << endl;
    core = get_unloaded_core(process_list);
    if(core == -1){
        cout << "Not found !" << endl;
        cout << termcolor::green << "Searching for a core that can fit the task... //TODO" << termcolor::reset << endl;
    }
    return core;
}

// TODO A voir si on ne devrait pas garder les process dans la liste et ajouter un champs "done" à la structure plutôt !
//process_list.erase(remove(process_list.begin(), process_list.end(), _task), process_list.end());


void launch_sequential(const char* filename) {

    //using namespace boost::interprocess;

    /*// Create or open (if created) a shared memory object
    managed_shared_memory segment(
            create_only,
            "MySharedMemory",
            65536);


    //Alias an STL-like allocator of ints that allocates ints from the segment
    typedef allocator<int, managed_shared_memory::segment_manager>
            ShmemAllocator;





    // Explicit call to destroy it
    shared_memory_object::remove("MySharedMemory");*/






    cout << "Launching scheduler in sequential mode..." << endl;

    vector<task> process_list;
    int q_id = msgget(ftok(filename, 0), 0);
    pid_t pid;
    int core;
    cpu_set_t set;

    task task_res;

    while(1){
        if(msgrcv(q_id, &task_res, 100, 1, 0) != -1) {
            CPU_ZERO(&set);

            task _task = task_res;
            cout << _task;

            // On choisit le CPU à affecter
            core = get_core_to_assign(process_list);
            CPU_SET(core, &set);
            _task.num_cpu = core;
            process_list.push_back(_task);

            pid = fork();
            switch(pid) {

                // Child's exec
                case 0:
                    if(sched_setaffinity(getpid(), sizeof(set), &set) == -1){
                        cout << termcolor::red << "SET_AFFINITY_ERROR" << termcolor::reset << endl;
                        exit(ERROR_SCHED_AFFINITY);
                    }
                    sleep(_task.duration);
                    print_process_handled(_task, core);
                    break;

                // Parent's exec
                default:
                    // Tell where the process has been dispatched
                    print_process_sent(pid, core);
                    break;
            }
        }
    }
}
