/*!
\file       util.h
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version    0.1
\date       01/04/2016
\brief      Util class declaration (functions printing a message)
\remarks    none
*/

#ifndef PROJETGSI_UTIL_H
#define PROJETGSI_UTIL_H

#include "../main.h"
#include "task.h"
#include <fstream>

/*!
\fn 		void print_process_handled(std::ostream &, task &, pid_t, int, int)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Print a message saying the process has been handled (execution finshed)
\remarks	none
\param 		stream reference to a stream
\param 		_task the task which will be write into the stream
\param 		pid task's process id
\param 		core core number which the task has been executed on
\param 		mseconds duration of the task's execution
*/
void print_process_handled(std::ostream &, task &, pid_t, int, int);

/*!
\fn 		void print_process_sent(std::ostream &, int, int)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Print a message saying the task has been sent to a core
\remarks	none
\param 		stream reference to a stream
\param 		pid task's process id
\param 		core core number which the task has been sent on
*/
void print_process_sent(std::ostream &, int, int);

/*!
\fn 		void print_cores_load(std::ostream &, const std::vector<double> &)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Print a message displaying the load of each core
\remarks	none
\param 		stream reference to a stream
\param 		cores_load list of each core's load
*/
void print_cores_load(std::ostream &, const std::vector<double> &);

/*!
\fn 		void print_process_incoming(std::ostream &, task &)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Print a message saying a process just arrived
\remarks	none
\param 		stream reference to a stream
\param 		_task reference to the task
*/
void print_process_incoming(std::ostream &, task &);

/*!
\fn 		void print_process_killed_timeout(std::ostream &, pid_t, task &)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Print a message saying the task has been killed because of the timeout
\remarks	none
\param 		stream reference to a stream
\param 		pid task's process id
\param 		_task reference to the task
*/
void print_process_killed_timeout(std::ostream &, pid_t, task &);

/*!
\fn 		void print_no_core_available(std::ostream &)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Print a message saying there is no core available to assign a task
\remarks	none
\param 		stream reference to a stream
*/
void print_no_core_available(std::ostream &);

/*!
\fn 		void print_set_affinity_error(std::ostream &)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Print a message saying there was an affinity error. The task has been sent to an incorrect core number
\remarks	none
\param 		stream nombre d'arguments en entrée du programme
*/
void print_set_affinity_error(std::ostream &);

/*!
\fn 		print_searching_unloaded_core(std::ostream &)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Print a message saying the scheduler is looking for an unloaded core
\remarks	none
\param 		stream reference to a stream
*/
void print_searching_unloaded_core(std::ostream &);

/*!
\fn 		void print_no_unloaded_core_found(std::ostream &)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Print a message saying the scheduler didn't find an unloaded core
\remarks	none
\param 		stream reference to a stream
*/
void print_no_unloaded_core_found(std::ostream &);

/*!
\fn 		void print_cannot_open_stream()
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Print a message saying there was an error when trying to open the file stream
\remarks	none
*/
void print_cannot_open_stream();

#endif //PROJETGSI_UTIL_H
