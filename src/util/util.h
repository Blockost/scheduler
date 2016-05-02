/*!
\file       util.h
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version    0.1
\date       01/04/2016
\brief      Util class declaration
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
\brief 		Lancement du programme en fonction des arguments entrée par l'utilisateur
\remarks	none
\param 		stream nombre d'arguments en entrée du programme
\param 		_task valeurs des arguments en entrée du programme
\param 		pid valeurs des arguments en entrée du programme
\param 		core valeurs des arguments en entrée du programme
\param 		mseconds valeurs des arguments en entrée du programme
*/
void print_process_handled(std::ostream &, task &, pid_t, int, int);

/*!
\fn 		void print_process_sent(std::ostream &, int, int)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Lancement du programme en fonction des arguments entrée par l'utilisateur
\remarks	none
\param 		stream nombre d'arguments en entrée du programme
\param 		pid nombre d'arguments en entrée du programme
\param 		core valeurs des arguments en entrée du programme
*/
void print_process_sent(std::ostream &, int, int);

/*!
\fn 		void print_cores_load(std::ostream &, const std::vector<double> &)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Lancement du programme en fonction des arguments entrée par l'utilisateur
\remarks	none
\param 		stream nombre d'arguments en entrée du programme
\param 		cores_load valeurs des arguments en entrée du programme
*/
void print_cores_load(std::ostream &, const std::vector<double> &);

/*!
\fn 		void print_process_incoming(std::ostream &, task &)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Lancement du programme en fonction des arguments entrée par l'utilisateur
\remarks	none
\param 		stream nombre d'arguments en entrée du programme
\param 		_task valeurs des arguments en entrée du programme
*/
void print_process_incoming(std::ostream &, task &);

/*!
\fn 		void print_process_killed_timeout(std::ostream &, pid_t, task &)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Lancement du programme en fonction des arguments entrée par l'utilisateur
\remarks	none
\param 		stream nombre d'arguments en entrée du programme
\param 		pid valeurs des arguments en entrée du programme
\param 		_task valeurs des arguments en entrée du programme
*/
void print_process_killed_timeout(std::ostream &, pid_t, task &);

/*!
\fn 		void print_no_core_available(std::ostream &)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Lancement du programme en fonction des arguments entrée par l'utilisateur
\remarks	none
\param 		stream nombre d'arguments en entrée du programme
*/
void print_no_core_available(std::ostream &);

/*!
\fn 		void print_set_affinity_error(std::ostream &)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Lancement du programme en fonction des arguments entrée par l'utilisateur
\remarks	none
\param 		stream nombre d'arguments en entrée du programme
*/
void print_set_affinity_error(std::ostream &);

/*!
\fn 		print_searching_unloaded_core(std::ostream &)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Lancement du programme en fonction des arguments entrée par l'utilisateur
\remarks	none
\param 		stream nombre d'arguments en entrée du programme
*/
void print_searching_unloaded_core(std::ostream &);

/*!
\fn 		void print_no_unloaded_core_found(std::ostream &)
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Lancement du programme en fonction des arguments entrée par l'utilisateur
\remarks	none
\param 		stream nombre d'arguments en entrée du programme
*/
void print_no_unloaded_core_found(std::ostream &);

/*!
\fn 		void print_cannot_open_stream()
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version 	0.1
\date       01/04/2016
\brief 		Lancement du programme en fonction des arguments entrée par l'utilisateur
\remarks	none
*/
void print_cannot_open_stream();

#endif //PROJETGSI_UTIL_H
