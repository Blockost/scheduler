#ifndef PROJETGSI_PARALLEL_SCHED_H
#define PROJETGSI_PARALLEL_SCHED_H

#include <sys/ipc.h>
#include <sys/msg.h>
#include <algorithm>
#include <signal.h>
#include "main.h"
#include <omp.h>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include "util/util.h"
#include <sys/wait.h>

typedef boost::interprocess::allocator<task, boost::interprocess::managed_shared_memory::segment_manager>  ShmemAllocator;
typedef boost::interprocess::vector<task, ShmemAllocator> VectorTasks;

int get_unloaded_core1(const double[]);
int get_less_loaded_core1(const double[]);
bool exist_suitable_core1(const double[], double);
void get_cores_load1(const VectorTasks&, double*);
int get_core_to_assign1(const VectorTasks&, double);

void launch_parallel(void);

#endif
