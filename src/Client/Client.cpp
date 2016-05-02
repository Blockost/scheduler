#include "Client.h"

using namespace boost::interprocess;
namespace pt = boost::property_tree; // Short alias for this namespace


Client::Client(std::string queue_name) :
        queue_name{queue_name},
        queue{open_or_create, queue_name.c_str(), 1000, sizeof(task)} {
}


Client::~Client() {
    //Destroy the queue if not in use
    message_queue::remove(queue_name.c_str());
}


void Client::send_one_process() {
    int u_timeout, u_priority;
    float f_load;
    std::string timeout, load, priority, command, tmp;

    std::cout << "--- Sending a new process to the queue ---" << std::endl;
    std::cout << "Command to execute (bash): $ ";
    getline(std::cin, tmp); // need for flushing
    getline(std::cin, command);
    std::cout << "Process timeout (> 0): ";
    std::cin >> timeout;
    std::cout << "Process load (0 <= load <= 1): ";
    std::cin >> load;
    std::cout << "Process priority (1: Low, 2: Normal, 3: High): ";
    std::cin >> priority;


    try {
        /* It's "verifying user inputs" time ...! */
        u_timeout = boost::lexical_cast<int>(timeout);
        f_load = boost::lexical_cast<float>(load);
        u_priority = boost::lexical_cast<int>(priority);
        if (u_timeout <= 0 || (f_load <0 && f_load > 1) || (u_priority != 1 && u_priority != 2 && u_priority != 3))
            throw boost::bad_lexical_cast();

        // If cast was successful
        task _task;
        _task.timeout = (unsigned) u_timeout;
        _task.load = f_load;
        _task.priority = (unsigned) u_priority;
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
        _task.timeout = (unsigned) (rand() % 11) + 1;
        _task.load = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        _task.priority = (unsigned) round(rand() % 3 + 1); // priority between 1 and 3
        strncpy(_task.command, array, 255);
        if (queue.try_send(&_task, sizeof(task), _task.priority)) {
            std::cout << termcolor::green << "Task successfully sent to the queue !" << termcolor::reset << std::endl;
        } else {
            std::cout << termcolor::red << "Task not sent... Queue is full !" << termcolor::reset << std::endl;
        }
    }
}

int Client::send_file_processes(){
    srand(time(NULL));
    char array[255] = "sleep 3 && echo \"This is a command \"";

    bool empty = true;

    pt::ptree root; // Create a root
    std::string tmp, path;
    task _task;
    int timeout, priority;
    float load;

    std::cout << "--- Enter the path of json file  ---" << std::endl;
    std::cin >> path;

    try
    {
        pt::read_json(path, root); // file path


        // Iterator over all task
        for (pt::ptree::value_type &list_task : root)
        {
            empty=false;
            tmp = list_task.second.get<std::string>("command",array); // default array
            strncpy(_task.command,tmp.c_str(),255);
            timeout = list_task.second.get<int>("timeout",(rand() % 11) + 1); // default (rand() % 11) + 1)
            load = list_task.second.get<float>("load", static_cast <float> (rand()) / static_cast <float> (RAND_MAX)); // default static_cast <float> (rand()) / static_cast <float> (RAND_MAX))
            priority = list_task.second.get<int>("priority",round(rand() % 3 + 1)); // default round(rand() % 3 + 1)

            if (timeout <0 || (priority <0 && priority>3) || (load<0 && load>1))
            {
                std::cout << termcolor::red << "Task cannot be created. Verify your json file."
                << termcolor::reset << std::endl;
                return ERROR_WRONG_JSON_STRUCTURE;
            }else{
                _task.timeout=(unsigned)timeout;
                _task.load=load;
                _task.priority=(unsigned)priority;
            }

            if (queue.try_send(&_task, sizeof(task), _task.priority)) {
                std::cout << termcolor::green << "Task successfully sent to the queue !" << termcolor::reset << std::endl;
            } else {
                std::cout << termcolor::red << "Task not sent... Queue is full !" << termcolor::reset << std::endl;
            }
        }

        if (empty) std::cout << "Your file is empty" << std::endl;


        return EXIT_SUCCESS;
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_FAILURE;
}

void Client::start() {

    std::string choice;


    do {
        do {
            std::cout << "--- CLIENT ---" << std::endl;
            std::cout << "1: Send 1 process" << std::endl;
            std::cout << "2: Send 3 processes with random attributes" << std::endl;
            std::cout << "3: Send processes from a json file" << std::endl;
            std::cout << "4: stop client" << std::endl;
            std::cin >> choice;
            try {
                boost::lexical_cast<int>(choice);
            } catch (boost::bad_lexical_cast) {
                std::cout << "\" " << choice << "\" is not a valid number" << std::endl;
                choice = "0";
            }
        } while (choice != "1" && choice != "2" && choice != "3" && choice != "4");


        if (choice == "1")
            send_one_process();

        if (choice == "2")
            send_several_processes(3);

        if (choice == "3")
            send_file_processes();

    } while (choice != "4");

    std::cout << "Client has been stopped." << std::endl;
}