#include <iostream>
#include "Scheduler.h"
#include "../flags.h"
#include "../util/util.h"


Scheduler::Scheduler(std::string filename) : file_logs{filename} {

    // If file exists, then remove it to erase its content
    if (file_logs) {
        file_logs.close();
        std::remove(filename.c_str());
    }

    file_logs.open(filename, std::fstream::out | std::fstream::app);

    if (!file_logs) {
        print_cannot_open_stream();
        exit(ERROR_OPEN_STREAM);
    }
}


Scheduler::~Scheduler() {
    file_logs.close();
}

