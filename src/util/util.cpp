/*!
\file       util.cpp
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version    0.1
\date       01/04/2016
\brief      Util class definition (functions printing a message)
\remarks    none
*/

#include "util.h"


void print_process_handled(std::ostream &stream, task &_task, pid_t pid, int core, int mseconds) {
    std::cout << "Process handled : "
    << mseconds << "ms"
    << " for " << _task.load << "CPU"
    << " by " << termcolor::green << "PID " << pid << termcolor::reset
    << " on " << termcolor::blue << "core" << core
    << termcolor::reset << std::endl;

    // Write into logs
    stream << "Process handled : "
    << mseconds << "ms"
    << " for " << _task.load << "CPU"
    << " by PID " << pid << " on core" << core
    << std::endl;
}

void print_process_sent(std::ostream &stream, int pid, int core) {

    std::cout << "Process delivered to PID " << pid
    << " on " << termcolor::blue << "core" << core
    << termcolor::reset << std::endl;

    stream << "Process delivered to PID " << pid
    << " on core " << core <<
    std::endl;

}


void print_cores_load(std::ostream &stream, const std::vector<double> &cores_load) {

    for (unsigned i = 0; i < cores_load.size(); ++i) {
        std::cout << "cpu" << i << ": "
        << cores_load[i] << "; ";
    }
    std::cout << std::endl;
    for (unsigned i = 0; i < cores_load.size(); ++i) {
        stream << "cpu" << i << ": "
        << cores_load[i] << "; ";
    }
    stream << std::endl;
}


void print_process_incoming(std::ostream &stream, task &_task) {
    std::cout << termcolor::blue << termcolor::on_white
    << "------------------------------------"
    << termcolor::reset << std::endl;
    std::cout << "New task arrived :" << _task << std::endl;

    stream << "**** New task arrived : "
    << _task << " **** " << std::endl;
}

void print_process_killed_timeout(std::ostream &stream, pid_t pid, task &_task) {
    std::cout << termcolor::red << "Process " << pid << " killed after " <<
    _task.timeout << "s of execution" << termcolor::reset << std::endl;

    stream << "Process " << pid << " killed after " <<
    _task.timeout << "s of execution" << std::endl;

}

void print_no_core_available(std::ostream &stream) {

    std::cout << termcolor::red
    << "No core available for the moment..."
    << termcolor::reset << std::endl;

    stream << "No core available for the moment..."
    << std::endl;
}

void print_set_affinity_error(std::ostream &stream) {
    std::cout << termcolor::red << termcolor::on_white
    << "SET_AFFINITY_ERROR"
    << termcolor::reset << std::endl;

    stream << "SET_AFFINITY_ERROR"
    << std::endl;
}


void print_searching_unloaded_core(std::ostream &stream) {
    std::cout << termcolor::blue << "Searching for an unloaded core..."
    << termcolor::reset << std::endl;

    stream << "Searching for an unloaded core..."
    << std::endl;

}

void print_no_unloaded_core_found(std::ostream &stream) {
    std::cout << termcolor::yellow
    << "No unloaded core found ! \n"
    << "Searching for a core that can fit the task..."
    << termcolor::reset << std::endl;

    stream << "No unloaded core found ! \n"
    << "Searching for a core that can fit the task..."
    << std::endl;
}

void print_cannot_open_stream() {
    std::cout << termcolor::red
    << "ERROR WHILE OPENING STREAM. Please execute the program with the WRITE permission on disk"
    << std::endl;
}



