#ifndef PROJETGSI_SEQ_SCHED_H
#define PROJETGSI_SEQ_SCHED_H

#include <sys/ipc.h>
#include <sys/msg.h>
#include <algorithm>
#include <signal.h>
#include "main.h"

void print_process_handled(task, int);
void print_process_sent(int, int);
int get_unloaded_core(const vector<task>);
float get_core_load(const vector<task>, int);
int get_core_to_assign(const vector<task>);
void launch_sequential(const char*);

#endif
