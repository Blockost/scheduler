#include "seq_sched.h"

void launch_sequential(const char* prog_name) {
    cout << "Launching scheduler in sequential mode..." << endl;

    struct task task;
    int q_id = msgget(ftok(prog_name, 0), 0);
    pid_t pid;
    int core;
    cpu_set_t set;

    while(1){
        if(msgrcv(q_id, &task, 100, 1, 0) != -1) {
            CPU_ZERO(&set);

            // On choisit le CPU à affecter
            srand(time(NULL));
            core = rand()%4;
            CPU_SET(core, &set);

            pid = fork();
            switch(pid) {
                case 0: //child
                    if (sched_setaffinity(getpid(), sizeof(set), &set) == -1)
                        exit(-3); //A CHECKER - FLAGS.h
                    sleep(task.duration);
                    cout << "Process handled : "
                    << task.duration << "s"
                    << " for " << task.load << "CPU"
                    << " by PID " << getpid()
                    << " on core number " << core
                    << endl;
                    break;
                default: //parent
                    // On choisit où affecter le processus
                    cout << "Process delivered to PID " << pid
                    << " on core number " << core
                    << endl;
                    break;
            }
        }
    }
}
