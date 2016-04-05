//
// Created by blockost on 12/03/16.
//

#ifndef PROJETGSI_TASK_H
#define PROJETGSI_TASK_H

#include <unistd.h>

class Task {

private:
    std::string name;
    unsigned int duration;
    float load;

public:
    Task(std::string name, unsigned int duration, float load) : name(name), duration(duration), load(load) { }

    void execute(void) {
        std::cout << "Executing task \"" << this->name << "\" (" << this->duration << " & " << this->load << ")\n";
        sleep(duration);
    }
};


#endif //PROJETGSI_TASK_H
