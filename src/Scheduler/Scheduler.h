/*!
\file       Scheduler.h
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version    0.1
\date       01/04/2016
\brief      Scheduler declaration class
\remarks    none
*/

#ifndef PROJETGSI_SCHEDULER_H
#define PROJETGSI_SCHEDULER_H


#include <string>
#include <fstream>
#include <boost/interprocess/sync/file_lock.hpp>

/*!\class   Scheduler
 * \brief   This is the base class for the scheduler. Only called by subclass constructor
 */
class Scheduler {

private:
    int ncores;                         /*!< Number of cores available for the scheduler */

protected:
    std::fstream file_logs;
    /*!< Stream to a local file. Used to write the scheduler's logs */
    std::vector<double> cores_load;     /*!< vector containing each core's load*/

    /*!
     *  \brief      Method initializing each core's load to 0
    */
    void initCores();

    /*!
     *  \brief      Pure virtual method. Will be implemented by the subclasses and never called.
     */
    virtual void start() = 0;


public:

    /*!
     *  \brief      Scheduler class constructor
     *  \param      filename name of the file which will be opened as the stream file_logs
     *  \param      ncores number of cores available for the scheduler
     */
    Scheduler(std::string, int);

    /*!
     *  \brief      Default scheduler destructor
     */
    virtual ~Scheduler();


};


#endif //PROJETGSI_SCHEDULER_H
