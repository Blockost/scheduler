#ifndef PROJETGSI_TASK_H
#define PROJETGSI_TASK_H

struct task {
    unsigned timeout = 0;
    float load = 0;
    int num_cpu = -1;
    unsigned priority = 0;
    char command[255];

    friend bool operator==(const task &left, const task &right){
        return left.timeout == right.timeout &&
               left.load == right.load &&
               left.num_cpu == right.num_cpu &&
               left.command[0] == right.command[0];
    }


    friend std::ostream &operator<<(std::ostream &out, const task &_task) {
        return out << "{ "
                    << termcolor::cyan << "command: " << _task.command
                    << termcolor::reset << "; "
                    << termcolor::magenta << "timeout: " << _task.timeout
                    << termcolor::reset << "; "
                    << termcolor::yellow << "load: " << _task.load
                    << termcolor::reset << "; "
                    << termcolor::green << "priority: " << _task.priority
                    << termcolor::reset << " }";
    }

};

#endif
