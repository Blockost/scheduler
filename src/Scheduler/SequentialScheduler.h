#ifndef PROJETGSI_SEQUENTIALSCHEDULER_H
#define PROJETGSI_SEQUENTIALSCHEDULER_H

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include <sys/wait.h>
#include "Scheduler.h"
#include "../task.h"
#include "../util/util.h"


typedef boost::interprocess::allocator<task,
        boost::interprocess::managed_shared_memory::segment_manager> ShmemAllocator;

typedef boost::interprocess::vector<task, ShmemAllocator> VectorTasks;

class SequentialScheduler : public Scheduler {

private:
    std::string filename;
    std::string queue_name;

    int get_unloaded_core(const double[]);

    int get_less_loaded_core(const double[]);

    bool exist_suitable_core(const double[], double);

    void get_cores_load(const VectorTasks &, double*);

    int get_core_to_assign(const VectorTasks &, double);

public:
    SequentialScheduler(const std::string &, const std::string &);

    virtual ~SequentialScheduler();

    virtual void start();


};


#endif //PROJETGSI_SEQUENTIALSCHEDULER_H
