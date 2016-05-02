/*!
\file       ParallelScheduler.h
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version    0.1
\date       01/04/2016
\brief      Parallel scheduler class declaration
\remarks    none
*/

#ifndef PROJETGSI_PARALLELSCHEDULER_H
#define PROJETGSI_PARALLELSCHEDULER_H

#include "Scheduler.h"
#include "SequentialScheduler.h"

typedef boost::interprocess::allocator<task,
        boost::interprocess::managed_shared_memory::segment_manager> ShmemAllocator;

typedef boost::interprocess::vector<task, ShmemAllocator> VectorTasks;

/*!\class   ParallelScheduler
 * \brief   classe representant le lecteur
 *
 *          La classe gere la lecture d'une liste de morceaux
 */
class ParallelScheduler : public Scheduler {

private:
    std::string filename;       /*!< Number of cores */
    std::string queue_name;     /*!< Number of cores */

    /*!
     *  \brief      Ajout d'un morceau
     *
     *              Methode qui permet d'ajouter un morceau a liste de
     *              lecture
     *
     *  \param      cores_load
     *  \return     return
     */
    int get_unloaded_core(const std::vector<double> &);

    /*!
     *  \brief      Ajout d'un morceau
     *
     *              Methode qui permet d'ajouter un morceau a liste de
     *              lecture
     *
     *  \param      cores_load
     *  \return     return
     */
    int get_less_loaded_core(const std::vector<double> &);

    /*!
     *  \brief      Ajout d'un morceau
     *
     *              Methode qui permet d'ajouter un morceau a liste de
     *              lecture
     *
     *  \param      cores_load : le morceau a ajouter
     *  \param      task_load : le morceau a ajouter
     *  \return     return
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
     *  \param      task_load
     *  \param      task_load
     *  \return     return
     */
    int get_core_to_assign(const VectorTasks &, double);

public:

    /*!
     *\brief        Constructeur
     *
     *              Destructeur de la classe CPlayer
     *\param        queue_name
     *\param        filename
     *\param        ncores
     */
    ParallelScheduler(std::string, std::string, int);

    /*!
     *  \brief      Destructeur
     *
     *              Destructeur de la classe CPlayer
     */
    virtual ~ParallelScheduler();

    /*!
     *  \brief      Destructeur
     *
     *              Destructeur de la classe CPlayer
     */
    virtual void start();

};


#endif //PROJETGSI_PARALLELSCHEDULER_H
