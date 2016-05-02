/*!
\file       Scheduler.h
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version    0.1
\date       01/04/2016
\brief      Scheduler class declaration
\remarks    none
*/

#ifndef PROJETGSI_SCHEDULER_H
#define PROJETGSI_SCHEDULER_H


#include <string>
#include <fstream>
#include <boost/interprocess/sync/file_lock.hpp>

/*!\class   Scheduler
 * \brief   classe representant le lecteur
 *
 *          La classe gere la lecture d'une liste de morceaux
 */
class Scheduler {

private:
    int ncores;                         /*!< Number of cores */

protected:
    std::fstream file_logs;             /*!< File_logs */
    std::vector<double> cores_load;     /*!< Cores_load */

    /*!
     *  \brief      Ajout d'un morceau
     *
     *              Methode qui permet d'ajouter un morceau a liste de
     *              lecture
     *
     */
    void initCores();

    /*!
     *  \brief      Ajout d'un morceau
     *
     *              Methode qui permet d'ajouter un morceau a liste de
     *              lecture
     *
     */
    virtual void start() = 0;


public:

    /*!
     *  \brief      Constructeur
     *
     *              Constructeur de la classe CPlayer
     *
     *  \param      filename : liste initial des morceaux
     *  \param      ncores : liste initial des morceaux
     */
    Scheduler(std::string, int);

    /*!
     *  \brief      Destructeur
     *
     *              Destructeur de la classe CPlayer
     */
    virtual ~Scheduler();


};


#endif //PROJETGSI_SCHEDULER_H
