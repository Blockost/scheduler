#include <boost/lexical_cast.hpp>
#include "server.h"

void start_server(const char* prg_name){
    key_t key = ftok(prg_name, 0);
    int q_id = msgget(key, 0);


    cout << q_id;
    if (q_id == -1) {
        q_id = msgget(key, IPC_CREAT | IPC_EXCL | 0666);
    }

    string choice;
    do{
        do{
            cout << "--- SERVER ---" << endl;
            cout << "1: Send processus" << endl;
            cout << "2: stop server" << endl;
            cin >> choice;
            try{
                boost::lexical_cast<int>(choice);
            }catch (boost::bad_lexical_cast){
                cout << "\" " << choice << "\" is not a valid number" << endl;
                choice = "0";
            }
        }while(choice != "1" && choice != "2");


        if(choice == "1"){
            cout << "--- Sending a new processus to the queue ---" << endl;
            task task;
            cout << "Process duration : ";
            cin >> task.duration;
            cout << "Process load : ";
            cin >> task.load;
            cout << "Process priority : ";
            cin >> task.priority;
            msgsnd(q_id, &task, 100, 0);
        }

    }while(choice != "2");
    cout << "Server stopped.";
}