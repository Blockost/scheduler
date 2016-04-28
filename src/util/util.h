//
// Created by blockost on 27/04/16.
//

#ifndef PROJETGSI_UTIL_H
#define PROJETGSI_UTIL_H

#include "../main.h"
#include "../task.h"
#include <fstream>
#include <sstream>


void write_into_stream(std::basic_ostream<char>&, std::stringstream&);

void print_process_handled(task&, pid_t, int, int);
void print_process_sent(int, int);
void print_cores_load(const double[]);
void print_process_incoming(task&);
void print_process_killed_timeout(task&, pid_t);
void print_no_core_available(void);
void print_set_affinity_error(void);
void print_searching_unloaded_core(void);
void print_no_unloaded_core_found(void);

#endif //PROJETGSI_UTIL_H
