#ifndef PROJETGSI_CLIENT_H
#define PROJETGSI_CLIENT_H

#include <boost/interprocess/ipc/message_queue.hpp>
#include "main.h"

void send_one_process(void);
void send_several_processes(unsigned);
void start_client(void);

#endif
