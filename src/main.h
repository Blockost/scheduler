/*!
\file       main.h
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version    0.1
\date       01/04/2016
\brief      Main declaration file of the whole program
\remarks    none
*/
#ifndef PROJETGSI_MAIN_H
#define PROJETGSI_MAIN_H

/* Built-in libraries */
#include <iostream>
#include <vector>
/* Boost libraries */
#include "termcolor/termcolor.hpp"
#include "boost/program_options.hpp"
/* Project libraries */
#include "util/flags.h"
#include "util/task.h"
#include "Scheduler/SequentialScheduler.h"
#include "Scheduler/ParallelScheduler.h"
#include "Client/Client.h"

/*!
\fn 		int main( int argc, char** argv)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Main function of the whole program. Start either the client or the scheduler.
\remarks	none
\param 		argc Number of arguments
\param 		argv Values of the arguments
\return 	ERROR_IN_CMD_LINE if the command line can't be parsed.
*/
int main(int argc, char **argv);

#endif
