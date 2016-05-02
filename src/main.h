/*!
\file       main.h
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version    0.1
\date       01/04/2016
\brief      Main declaration
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
\brief 		Lancement du programme en fonction des arguments entrée par l'utilisateur
\remarks	none
\param 		argc nombre d'arguments en entrée du programme
\param 		argv valeurs des arguments en entrée du programme
\return 	0 si tout va bien
*/
int main(int argc, char **argv);

#endif
