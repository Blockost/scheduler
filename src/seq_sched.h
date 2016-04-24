#ifndef PROJETGSI_SEQ_SCHED_H
#define PROJETGSI_SEQ_SCHED_H

#include <sys/ipc.h>
#include <sys/msg.h>
#include <algorithm>
#include <signal.h>
#include "main.h"

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

using namespace boost::interprocess;

typedef allocator<task, managed_shared_memory::segment_manager>  ShmemAllocator;
typedef vector<task, ShmemAllocator> VectorTasks;

void print_process_handled(task, int);
void print_process_sent(int, int);
void print_cores_load(const float[]);
int get_unloaded_core(const float[]);
int get_less_loaded_core(const float[]);
bool exist_suitable_core(const float[], float);
void get_cores_load(const VectorTasks&, float*);
int get_core_to_assign(const VectorTasks&, float);
void launch_sequential(void);

#endif
