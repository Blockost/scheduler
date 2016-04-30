#include "Client.h"

using namespace boost::interprocess;

Client::Client(std::string queue_name) :
        queue_name{queue_name},
        queue{open_or_create, queue_name.c_str(), 1000, sizeof(task)} {

}


Client::~Client() {
    //Destroy the queue if not in use
    message_queue::remove(queue_name.c_str());
}


void Client::send_one_process() {
    unsigned u_duration, u_priority;
    float f_load;
    std::string duration, load, priority, command, tmp;

    std::cout << "--- Sending a new process to the queue ---" << std::endl;
    std::cout << "Command to execute (bash): $ ";
    getline(std::cin, tmp); // need for flushing
    getline(std::cin, command);
    std::cout << "Process timeout (> 0): ";
    std::cin >> duration;
    std::cout << "Process load (0 <= load <= 1): ";
    std::cin >> load;
    std::cout << "Process priority (1: Low, 2: Normal, 3: High): ";
    std::cin >> priority;


    try {
        /* It's "verifying user inputs" time ...! */
        u_duration = boost::lexical_cast<unsigned>(duration);
        f_load = boost::lexical_cast<float>(load);
        u_priority = boost::lexical_cast<unsigned>(priority);
        if (u_duration == 0 || f_load > 1 || (u_priority != 1 && u_priority != 2 && u_priority != 3))
            throw boost::bad_lexical_cast();

        // If cast was successful
        task _task;
        _task.timeout = u_duration;
        _task.load = f_load;
        _task.priority = u_priority;
        strncpy(_task.command, command.c_str(), 255);

        try {
            // Send the message
            queue.send(&_task, sizeof(task), _task.priority);
            std::cout << termcolor::green << "Task successfully sent to the queue !"
            << termcolor::reset << std::endl;
        } catch (interprocess_exception &ex) {
            std::cout << ex.what() << std::endl;
        }
    } catch (boost::bad_lexical_cast e) {
        std::cout << termcolor::red << "Task cannot be created. Try to enter consistent values"
        << termcolor::reset << std::endl;
    }
}

void Client::send_several_processes(unsigned nb_processes) {
    srand(time(NULL));
    char array[255] = "sleep 3 && echo \"This is a command \"";
    for (unsigned i = 0; i < nb_processes; ++i) {
        task _task;
        _task.timeout = (rand() % 11) + 1;
        _task.load = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        _task.priority = round(rand() % 3 + 1); // génère une priorité entre 1 et 3.
        strncpy(_task.command, array, 255);
        std::cout << "created : " << _task << std::endl;
        if (queue.try_send(&_task, sizeof(task), _task.priority)) {
            std::cout << termcolor::green << "Task successfully sent to the queue !" << termcolor::reset << std::endl;
        } else {
            std::cout << termcolor::red << "Task not sent... Queue is full !" << termcolor::reset << std::endl;
        }
    }
}

void Client::start() {

    std::string choice;


    do {
        do {
            std::cout << "--- CLIENT ---" << std::endl;
            std::cout << "1: Send 1 process" << std::endl;
            std::cout << "2: Send 3 processes with random attributes" << std::endl;
            std::cout << "3: stop client" << std::endl;
            std::cin >> choice;
            try {
                boost::lexical_cast<int>(choice);
            } catch (boost::bad_lexical_cast) {
                std::cout << "\" " << choice << "\" is not a valid number" << std::endl;
                choice = "0";
            }
        } while (choice != "1" && choice != "2" && choice != "3");


        if (choice == "1")
            send_one_process();

        if (choice == "2")
            send_several_processes(3);

    } while (choice != "3");

    std::cout << "Client has been stopped." << std::endl;
}