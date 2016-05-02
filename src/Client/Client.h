/*!
\file       Client.h
\author     Simon ESPIGOLÉ - Teddy GILBERT - Hugo LEGRAND
\version    0.1
\date       01/04/2016
\brief      Client declaration class
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
 * \brief   Class which defines a client sending tasks to a message queue.
 */
class Client {

private:
    std::string queue_name;                     /*!< Queue_name */
    boost::interprocess::message_queue queue;   /*!< Queue */

    /*!
     *\brief        Method to send only one process to the queue
     */
    void send_one_process();

    /*!
     *\brief        Method to send several processes to the queue
     *\param        Number of processes to send
     */
    void send_several_processes(unsigned);

    /*!
     *\brief        Method to send several processes which are defined in a JSON file
     */
    int send_file_processes();

public:

    /*!
     *\brief        Client class constructor
     *\param        queue_name the name of the queue
     */
    Client(std::string);

    /*!
     *\brief        Default destructor of the class
     */
    ~Client();

    /*!
     *\brief        This function starts the client
     */
    void start();
};


#endif //PROJETGSI_CLIENT_H
