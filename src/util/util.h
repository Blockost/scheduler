#ifndef PROJETGSI_UTIL_H
#define PROJETGSI_UTIL_H

#include "../main.h"
#include "../task.h"
#include <fstream>

void print_process_handled(std::ostream &, task &, pid_t, int, int);

void print_process_sent(std::ostream &, int, int);

void print_cores_load(std::ostream &, const double[]);

void print_process_incoming(std::ostream &, task &);

void print_process_killed_timeout(std::ostream &, pid_t, task &);

void print_no_core_available(std::ostream &);

void print_set_affinity_error(std::ostream &);

void print_searching_unloaded_core(std::ostream &);

void print_no_unloaded_core_found(std::ostream &);

void print_cannot_open_stream();

#endif //PROJETGSI_UTIL_H
