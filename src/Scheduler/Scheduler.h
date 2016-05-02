#ifndef PROJETGSI_SCHEDULER_H
#define PROJETGSI_SCHEDULER_H


#include <string>
#include <fstream>
#include <boost/interprocess/sync/file_lock.hpp>

class Scheduler {

private:
    int ncores;

protected:
    std::fstream file_logs;
    std::vector<double> cores_load;

    void initCores();

    virtual void start() = 0;


public:
    Scheduler(std::string, int);

    virtual ~Scheduler();


};


#endif //PROJETGSI_SCHEDULER_H
