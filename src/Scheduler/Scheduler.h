#ifndef PROJETGSI_SCHEDULER_H
#define PROJETGSI_SCHEDULER_H


#include <string>
#include <fstream>
#include <boost/interprocess/sync/file_lock.hpp>

class Scheduler {

protected:
    std::fstream file_logs;

    virtual void start() = 0;

public:
    Scheduler(std::string);

    virtual ~Scheduler();


};


#endif //PROJETGSI_SCHEDULER_H
