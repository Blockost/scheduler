//
// Created by blockost on 12/03/16.
//

#ifndef PROJETGSI_TASK_H
#define PROJETGSI_TASK_H

#include "boost/date_time/posix_time/posix_time.hpp"

using namespace boost::posix_time;

class Task {

public:
    Task(){ };

private:
    std::string name;
    time_duration duration;

public:
    void execute(void) {
        std::cout << "Executing task \"" << this->name << "\" (" << this->duration << ")\n";
    }

    Task(std::string name, time_duration *duration) : name(name), duration(*duration) { }
};


#endif //PROJETGSI_TASK_H
