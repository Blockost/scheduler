#include "seq_sched.h"


void launch_sequential(const char* prog_name) {
    cout << "Launching scheduler in sequential mode..." << endl;

    struct task task;
    int q_id = msgget(ftok(prog_name, 0), 0);

    while(1){
        if(msgrcv(q_id, &task, 100, 1, 0) != -1)
            cout << "Process handled : "
            << task.duration
            << " | " << task.load
            << endl;
    }
}
