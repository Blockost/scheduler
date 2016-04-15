#ifndef PROJETGSI_MAIN_H
#define PROJETGSI_MAIN_H

#include <iostream>
#include "termcolor/termcolor.hpp"
#include <vector>
#include "flags.h"
#include "boost/program_options.hpp"
#include "server.h"

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
    unsigned priority =0;
};


struct less_than_key
{
    inline bool operator() (const task& struct1, const task& struct2)
    {
        return (struct1.priority < struct2.priority);
    }
};



#endif
