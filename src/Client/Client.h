/*!
\file       Client.h
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version    0.1
\date       01/04/2016
\brief      Client class declaration
\remarks    none
*/
#ifndef PROJETGSI_CLIENT_H
#define PROJETGSI_CLIENT_H


#include <boost/interprocess/ipc/message_queue.hpp>
#include "../main.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional/optional.hpp>

/*!\class   Client
 * \brief   classe representant le lecteur
 *
 *          La classe gere la lecture d'une liste de morceaux
 */
class Client {

private:
    std::string queue_name;                     /*!< Queue_name */
    boost::interprocess::message_queue queue;   /*!< Queue */

    /*!
     *\brief        Ajout d'un morceau
     *
     *              Methode qui permet d'ajouter un morceau a liste de
     *              lecture
     */
    void send_one_process();

    /*!
     *\brief        Ajout d'un morceau
     *
     *              Methode qui permet d'ajouter un morceau a liste de
     *              lecture
     *\param        nb_processes
     */
    void send_several_processes(unsigned);

    /*!
     *\brief        Ajout d'un morceau
     *
     *              Methode qui permet d'ajouter un morceau a liste de
     *              lecture
     *\return       int
     */
    int send_file_processes();

public:

    /*!
     *\brief        Destructeur
     *
     *              Destructeur de la classe CPlayer
     *\param        queue_name
     */
    Client(std::string);

    /*!
     *\brief        Destructeur
     *
     *              Destructeur de la classe CPlayer
     */
    ~Client();

    /*!
     *\brief        Destructeur
     *
     *              Destructeur de la classe CPlayer
     */
    void start();
};


#endif //PROJETGSI_CLIENT_H
