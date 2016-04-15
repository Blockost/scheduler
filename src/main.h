#ifndef PROJETGSI_MAIN_H
#define PROJETGSI_MAIN_H

#include <iostream>
#include "termcolor/termcolor.hpp"
#include <vector>
#include "Task.h"
#include "flags.h"

using namespace std;

struct task {
    long mtype = 1;
    unsigned int duration = 0;
    float load = 0;
    int num_cpu = -1;

    friend bool operator==(const task &left, const task &right){
        return left.duration == right.duration &&
               left.load == right.load &&
               left.num_cpu == right.num_cpu;
    }


    friend ostream &operator<<(ostream &out, const task &_task) {
        return out << "{"
               << _task.duration
               << "; "
               << _task.load
               << "; "
               << _task.num_cpu
               << "}"
               << endl;
    }
};

#endif
