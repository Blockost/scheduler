#include "util.h"



void write_into_stream(std::basic_ostream<char>& out, std::stringstream& ss) {
    if(out){
        std::string s = ss.str();
        out << s;
        ss.flush();
        out.flush();
    }
}

//TODO Make writing into a stream generic : std::cout or std::fstream -> print_blabla(WRITE_INTO_FILE | WRITE_INTO_CONSOLE, ...)
void print_process_handled(task& _task, int core) {
    std::cout << "Process handled : "
    // TODO: process isn't handled anymmore in 'timeout' seconds : get real time
    << _task.timeout << "s"
    << " for " << _task.load << "CPU"
    << " by " << termcolor::green << "PID " << getpid() << termcolor::reset
    << " on " << termcolor::blue << "core" << core
    << termcolor::reset << std::endl;
}

void print_process_sent(int pid, int core) {
    std::cout << "Process delivered to PID " << pid
    << " on " << termcolor::blue << "core" << core
    << termcolor::reset << std::endl;
}

void print_cores_load(const double cores_load[4]){
    for(unsigned i = 0; i < 4; ++i) {
        std::cout << "cpu" << i << ": "
        << cores_load[i] << "; ";
    }
    std::cout << std::endl;
}

void print_process_incoming(task& _task){
    std::cout << termcolor::blue << termcolor::on_white
    << "------------------------------------"
    << termcolor::reset << std::endl;
    std::cout << "New task arrived :" << _task << std::endl;
}

void print_process_killed_timeout(pid_t exec, task& _task) {
    std::cout << termcolor::red << "Process " << exec << " killed after " <<
    _task.timeout << "s of execution" << termcolor::reset << std::endl;
}

void print_no_core_available(){
    std::cout << termcolor::red
    << "No core available for the moment..."
    << termcolor::reset << std::endl;
}

void print_set_affinity_error(){
    std::cout << termcolor::red << termcolor::on_white
    << "SET_AFFINITY_ERROR"
    << termcolor::reset << std::endl;
}


void print_searching_unloaded_core() {
    std::cout << termcolor::blue << "Searching for an unloaded core..."
    << termcolor::reset << std::endl;
}

void print_no_unloaded_core_found() {
    std::cout << termcolor::yellow << "No unloaded core found !"
        << std::endl;
    std::cout << "Searching for a core that can fit the task..."
        << termcolor::reset << std::endl;
}



