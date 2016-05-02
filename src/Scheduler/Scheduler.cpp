/*!
\file       Scheduler.cpp
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version    0.1
\date       01/04/2016
\brief      Scheduler definition class
\remarks    none
*/
#include <iostream>
#include "Scheduler.h"
#include "../util/flags.h"
#include "../util/util.h"


Scheduler::Scheduler(std::string filename, int ncores) :
        ncores{ncores}, file_logs{filename}, cores_load{0} {

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


void Scheduler::initCores() {
    cores_load.clear();
    for (int i = 0; i < ncores; i++) {
        cores_load.push_back(0);
    }
}



