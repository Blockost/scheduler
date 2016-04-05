#ifndef PROJETGSI_MAIN_H
#define PROJETGSI_MAIN_H

#include <iostream>

#include <json/json.h>
#include "Task.h"
#include "boost/program_options.hpp"
#include "seq_sched.h"
#include "parallel_sched.h"
#include "server.h"

using namespace std;

struct task {
    long mtype = 1;
    unsigned int duration = 0;
    float load = 0;
};

#endif
