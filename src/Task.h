//
// Created by blockost on 12/03/16.
//

#ifndef PROJETGSI_TASK_H
#define PROJETGSI_TASK_H


class Task {

private:
    std::string name;
    int duration;

public:
    void execute(void) {
        std::cout << "Executing task \"" << this->name << "\" (" << this->duration << "ms)\n";
    }

    Task(std::string name, int duration) : name(name), duration(duration) { }
};


#endif //PROJETGSI_TASK_H
