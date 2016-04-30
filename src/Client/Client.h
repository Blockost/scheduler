#ifndef PROJETGSI_CLIENT_H
#define PROJETGSI_CLIENT_H


#include <boost/interprocess/ipc/message_queue.hpp>
#include "../main.h"


class Client {

private:
    std::string queue_name;
    boost::interprocess::message_queue queue;

    void send_one_process(void);

    void send_several_processes(unsigned);


public:
    Client(std::string);

    ~Client();

    void start(void);
};


#endif //PROJETGSI_CLIENT_H
