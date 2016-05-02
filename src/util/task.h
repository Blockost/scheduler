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
*               Structure allowing to manipulate complex data type: a task.
* \remarks      none
*/
struct task {
    unsigned timeout = 0;
    /*!< Timemout: number of seconds to wait before killing the task*/
    float load = 0;
    /*!< Load: define the cpu load the task will take*/
    int num_cpu = -1;
    /*!< Num_cpu: cpu index which the task is assigned on */
    unsigned priority = 0;
    /*!< Priority: define task's weight */
    char command[255];      /*!< Command: define the command which will be executed by the processor handling the task*/

    /*!
     *  \brief      Overload the equal operator for comparison
     *  \param      left: first task
     *  \param      right: second task
     *  \return     true if tasks are the same, false otherwise
     */
    friend bool operator==(const task &left, const task &right){
        return left.timeout == right.timeout &&
               left.load == right.load &&
               left.num_cpu == right.num_cpu &&
               left.command[0] == right.command[0];
    }

    /*!
     *  \brief      Overload the stream redirection
     *  \param      out: stream reference
     *  \param      _task : reference to the task that will be write into the stream
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
