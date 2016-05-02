/*!
\file       SequentialScheduler.h
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version    0.1
\date       01/04/2016
\brief      Sequential scheduler declaration class
\remarks    none
*/

#ifndef PROJETGSI_SEQUENTIALSCHEDULER_H
#define PROJETGSI_SEQUENTIALSCHEDULER_H

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include <sys/wait.h>
#include <omp.h>
#include "Scheduler.h"
#include "../util/task.h"
#include "../util/util.h"


typedef boost::interprocess::allocator<task,
        boost::interprocess::managed_shared_memory::segment_manager> ShmemAllocator;

typedef boost::interprocess::vector<task, ShmemAllocator> VectorTasks;

/*!\class   SequentialScheduler
 * \brief   Class modeling a sequential scheduler
 */
class SequentialScheduler : public Scheduler {

private:
    std::string filename;
    /*!< ame of the file which will be opened as the stream file_logs */
    std::string queue_name; /*!< Name of the queue */

    /*!
     *  \brief      Method looking for an unloaded core and returning its index
     *  \param      cores_load vector containing the load of each core
     *  \return     index of the unloaded core or -1 if no core
     */
    int get_unloaded_core(const std::vector<double> &);

    /*!
     *  \brief      Method looking for the less loaded core
     *  \param      cores_load vector containing the load of each core
     *  \return     index of the less loaded core
     */
    int get_less_loaded_core(const std::vector<double> &);

    /*!
     *  \brief      Method looking for a core which can handle the task
     *  \param      cores_load vector containing the load of each core
     *  \param      task_load the task's load
     *  \return     true if a core exists, false otherwise
     */
    bool exist_suitable_core(const std::vector<double> &, double);

    /*!
     *  \brief      Method retrieving the load of each core and filling cores_load with the data
     *  \param      process_list vector containing the tasks which are assigned to a core
     *  \param      cores_load vector containing the load of each core
     */
    void get_cores_load(const VectorTasks &, std::vector<double> &);

    /*!
     *  \brief      Main method looking for a core that can handle the task
     *  \param      process_list vector containing the tasks that which are assigned to a core
     *  \param      task_load the load of the task
     *  \return     index of the core if there's one, -1 otherwise
     */
    int get_core_to_assign(const VectorTasks &, double);

public:

    /*!
     *  \brief      Sequential scheduler class constructor
     *  \param      queue_name the name of the message queue
     *  \param      filename name of the file which will be opened as the stream file_logs
     *  \param      ncores number of cores available for the scheduler
     */
    SequentialScheduler(const std::string &, const std::string &, int);

    /*!
     *  \brief      Default sequential scheduler class destructor
     */
    virtual ~SequentialScheduler();

    /*!
     *  \brief      This method starts the scheduler in sequential mode
     */
    virtual void start();


};


#endif //PROJETGSI_SEQUENTIALSCHEDULER_H
