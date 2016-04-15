#include <fstream>
#include "main.h"
#include "flags.h"


namespace po = boost::program_options;

int main(int argc, char** argv) {

    po::options_description desc("Options");
    po::variables_map vm;

    Json::Value root;
    Json::Reader reader;
    Json::Value tasks;

    vector<task> pool;

    string filename = "tasks.json";

    // Define all available options
    desc.add_options()
            ("help,h", "Print this help message")
            ("server", "Start the server to populate the queue")
            ("include-file,i", po::value<string>(), "Specify the file to include. If not specified, it will be parsed \"tasks.json\""
                    " at the executable's location")
            ("sequential,s", "Launch the scheduler in sequential mode")
            ("parallel,p", "Launch the scheduler in parallel mode")
            ("distrib,d", "Launch the scheduler in distributed mode");
            //("foo", po::value<std::string>()->implicit_value("")->zero_tokens()->notifier(&func),"foo description");

    try{

        // Parse options in cmd line
        po::store(po::parse_command_line(argc, argv, desc),vm);

        /* Help option */
        if(vm.count("help")) {
            cout << desc;
        }


        if(vm.count(",f")) {
            vm.notify();
        }

        /* Launch sched in sequential mode */
        if(vm.count("sequential")){
            launch_sequential(argv[0]);
        }

        /* Lauch the server */
        if(vm.count("server")){
            start_server(argv[0]);
        }

        if(vm.count("paralel")){
            launch_parallel();
        }


    // If the option is unrecognised...
    }catch (po::error &e){
        cerr << e.what() << endl;
        return ERROR_IN_CMD_LINE;
    }
}
