#ifndef PROJETGSI_PARALLELSCHEDULER_H
#define PROJETGSI_PARALLELSCHEDULER_H

#include "Scheduler.h"
#include "SequentialScheduler.h"

typedef boost::interprocess::allocator<task,
        boost::interprocess::managed_shared_memory::segment_manager> ShmemAllocator;

typedef boost::interprocess::vector<task, ShmemAllocator> VectorTasks;

class ParallelScheduler : public Scheduler {

private:
    std::string filename;
    std::string queue_name;

    int get_unloaded_core(const double[]);

    int get_less_loaded_core(const double[]);

    bool exist_suitable_core(const double[], double);

    void get_cores_load(const VectorTasks &, double[]);

    int get_core_to_assign(const VectorTasks &, double);

public:
    ParallelScheduler(std::string, std::string);

    virtual ~ParallelScheduler();

    virtual void start();
};


#endif //PROJETGSI_PARALLELSCHEDULER_H
