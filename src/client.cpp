#include "client.h"

using namespace std;
using namespace boost::interprocess;

message_queue queue(open_or_create, "scheduler_queue", 1000, sizeof(task));

void send_one_process(){
    unsigned u_duration, u_priority;
    float f_load;
    std::string duration, load, priority, command, tmp;

    cout << "--- Sending a new process to the queue ---" << endl;
    cout << "Command to execute (bash): $ ";
    getline(cin, tmp); // need for flushing
    getline(cin, command);
    cout << "Process timeout (> 0): ";
    cin >> duration;
    cout << "Process load (0 <= load <= 1): ";
    cin >> load;
    cout << "Process priority (1: Low, 2: Normal, 3: High): ";
    cin >> priority;


    try {
        /* It's "verifying user inputs" time ...! */
        u_duration = boost::lexical_cast<unsigned>(duration);
        f_load = boost::lexical_cast<float>(load);
        u_priority = boost::lexical_cast<unsigned>(priority);
        if(u_duration == 0 || f_load > 1 || (u_priority != 1 && u_priority != 2 && u_priority != 3))
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
            cout << termcolor::green << "Task successfully sent to the queue !" << termcolor::reset << endl;
        }catch (interprocess_exception &ex) {
            std::cout << ex.what() << std::endl;
        }
    }catch (boost::bad_lexical_cast e){
        cout << termcolor::red << "Task cannot be created. Try to enter consistent values"
        << termcolor::reset << endl;
    }
}

void send_several_processes(unsigned nb_processes){
    srand(time(NULL));
    char array[255] = "sleep 3 && echo \"This is a command \"";
    for(unsigned i = 0; i < nb_processes; ++i){
        task _task;
        _task.timeout = rand() % 11;
        _task.load = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        _task.priority = round(rand()%2+1);
        strncpy(_task.command, array, 255);
        cout << "created : " << _task << endl;
        if(queue.try_send(&_task, sizeof(task), _task.priority)){
            cout << termcolor::green << "Task successfully sent to the queue !" << termcolor::reset << endl;
        }else{
            cout << termcolor::red << "Task not sent... Queue is full !" << termcolor::reset << endl;
        }
    }
}

void start_client(){

    string choice;


    do{
        do{
            cout << "--- CLIENT ---" << endl;
            cout << "1: Send 1 process" << endl;
            cout << "2: Send 3 processes with random attributes" << endl;
            cout << "3: stop client" << endl;
            cin >> choice;
            try{
                boost::lexical_cast<int>(choice);
            }catch (boost::bad_lexical_cast){
                cout << "\" " << choice << "\" is not a valid number" << endl;
                choice = "0";
            }
        }while(choice != "1" && choice != "2" && choice != "3");


        if(choice == "1")
            send_one_process();

        if(choice == "2")
            send_several_processes(3);

    }while(choice != "3");

    // Destroy the queue if not in use
    message_queue::remove("scheduler_queue");

    cout << "Client has been stopped." << endl;
}