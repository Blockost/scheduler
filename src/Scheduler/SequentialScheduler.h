/*!
\file       SequentialScheduler.h
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version    0.1
\date       01/04/2016
\brief      Sequential scheduler class declaration
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
 * \brief   classe representant le lecteur
 *
 *          La classe gere la lecture d'une liste de morceaux
 */
class SequentialScheduler : public Scheduler {

private:
    std::string filename;   /*!< Filemane */
    std::string queue_name; /*!< Queue_name */

    /*!
     *  \brief      Ajout d'un morceau
     *
     *              Methode qui permet d'ajouter un morceau a liste de
     *              lecture
     *
     *  \param      cores_load
     *  \return     true si morceau deja present dans la liste, false sinon
     */
    int get_unloaded_core(const std::vector<double> &);

    /*!
     *  \brief      Ajout d'un morceau
     *
     *              Methode qui permet d'ajouter un morceau a liste de
     *              lecture
     *
     *  \param      cores_load
     *  \return     true si morceau deja present dans la liste, false sinon
     */
    int get_less_loaded_core(const std::vector<double> &);

    /*!
     *  \brief      Ajout d'un morceau
     *
     *              Methode qui permet d'ajouter un morceau a liste de
     *              lecture
     *
     *  \param      cores_load
     *  \param      task_load
     *  \return     true si morceau deja present dans la liste, false sinon
     */
    bool exist_suitable_core(const std::vector<double> &, double);

    /*!
     *  \brief      Ajout d'un morceau
     *
     *              Methode qui permet d'ajouter un morceau a liste de
     *              lecture
     *
     *  \param      process_list
     *  \param      cores_load
     */
    void get_cores_load(const VectorTasks &, std::vector<double> &);

    /*!
     *  \brief      Ajout d'un morceau
     *
     *              Methode qui permet d'ajouter un morceau a liste de
     *              lecture
     *
     *  \param      process_list
     *  \param      task_load
     *  \return     true si morceau deja present dans la liste, false sinon
     */
    int get_core_to_assign(const VectorTasks &, double);

public:

    /*!
     *  \brief      Constructeur
     *
     *              Constructeur de la classe CPlayer
     *
     *  \param      queue_name : liste initial des morceaux
     *  \param      filename : liste initial des morceaux
     *  \param      ncores : liste initial des morceaux
     */
    SequentialScheduler(const std::string &, const std::string &, int);

    /*!
     *  \brief      Destructeur
     *
     *              Destructeur de la classe CPlayer
     */
    virtual ~SequentialScheduler();

    /*!
     *  \brief      Destructeur
     *
     *              Destructeur de la classe CPlayer
     */
    virtual void start();


};


#endif //PROJETGSI_SEQUENTIALSCHEDULER_H
