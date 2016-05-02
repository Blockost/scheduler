/*!
\file       task.h
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version    0.1
\date       01/04/2016
\brief      Task structure declaration
\remarks    none
*/

#ifndef PROJETGSI_TASK_H
#define PROJETGSI_TASK_H

#include <fstream>
#include "termcolor/termcolor.hpp"

/*! \struct     task
*               Structure pour la manipulation de nombre complexe algébrique
* \remarks      Les nombres sont sous la forme \f$a+ib \f$
*/
struct task {
    unsigned timeout = 0;   /*!< Timemout */
    float load = 0;         /*!< Load */
    int num_cpu = -1;       /*!< Num_cpu */
    unsigned priority = 0;  /*!< Priority */
    char command[255];      /*!< Command */

    /*!
     *  \brief      Ajout d'un morceau
     *
     *              Methode qui permet d'ajouter un morceau a liste de
     *              lecture
     *
     *  \param      left : le morceau a ajouter
     *  \param      right : le morceau a ajouter
     *  \return     true si morceau deja present dans la liste, false sinon
     */
    friend bool operator==(const task &left, const task &right){
        return left.timeout == right.timeout &&
               left.load == right.load &&
               left.num_cpu == right.num_cpu &&
               left.command[0] == right.command[0];
    }

    /*!
     *  \brief      Ajout d'un morceau
     *
     *              Methode qui permet d'ajouter un morceau a liste de
     *              lecture
     *
     *  \param      out : le morceau a ajouter
     *  \param      _task : le morceau a ajouter
     *  \return     true si morceau deja present dans la liste, false sinon
     */
    friend std::ostream &operator<<(std::ostream &out, const task &_task) {
        // Check if the stream is stdout or not
        if (out.rdbuf() == std::cout.rdbuf()) {
            out << "{ " << termcolor::cyan
            << termcolor::cyan << "command: \"" << _task.command
            << termcolor::reset << "\"; "
            << termcolor::magenta << "timeout: " << _task.timeout
            << termcolor::reset << "; "
            << termcolor::yellow << "load: " << _task.load
            << termcolor::reset << "; "
            << termcolor::green << "priority: " << _task.priority
            << termcolor::reset << " }";
        } else {
            out << "{ "
            << "command: \"" << _task.command
            << "\"; timeout: " << _task.timeout
            << "; load: " << _task.load
            << "; priority: " << _task.priority
            << " }";
        }

        return out;
    }

};

#endif
