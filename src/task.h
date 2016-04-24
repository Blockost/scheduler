#ifndef PROJETGSI_TASK_H
#define PROJETGSI_TASK_H

struct task {
    unsigned duration = 0;
    float load = 0;
    int num_cpu = -1;
    unsigned priority = 0;


    friend bool operator==(const task &left, const task &right){
        return left.duration == right.duration &&
               left.load == right.load &&
               left.num_cpu == right.num_cpu;
    }


    friend std::ostream &operator<<(std::ostream &out, const task &_task) {
        return out << "{"
               << "duration: " << _task.duration
               << "; "
               << "load: " << _task.load
               << "; "
               << "priority: " << _task.priority
               << "; "
               << "cpu: " << _task.num_cpu
               << "}";
    }

};

#endif
