#include <fstream>
#include "boost/program_options.hpp"

#include "main.h"
#include "seq_sched.h"
#include "parallel_sched.h"


namespace po = boost::program_options;

int main(int argc, char** argv) {

    po::options_description desc("Options");
    po::variables_map vm;

    // Define all available options
    desc.add_options()
            ("help,h", "Print this help message")
            ("client,c", "Start the client to populate the queue")
            /*("include-file,i", po::value<std::string>(), "Specify the file to include. If not specified, it will be parsed the hidden file \".file\" "
                    "at the executable's location")*/
            ("sequential,s", "Launch the scheduler in sequential mode")
            ("parallel,p", "Launch the scheduler in parallel mode")
            ("distrib,d", "Launch the scheduler in distributed mode");

    try{

        // Parse options in cmd line
        po::store(po::parse_command_line(argc, argv, desc),vm);

        /* Help option */
        if(vm.count("help")) {
            std::cout << desc;
        }


        if(vm.count(",f")) {
            vm.notify();
        }

        /* Launch the server */
        if(vm.count("client")){
            start_client();
        }

        //TODO Add logs to keep track of the scheduler's behaviour

        /* Launch sched in sequential mode */
        if(vm.count("sequential")){
            launch_sequential();
        }

        if(vm.count("paralel")){
            launch_parallel();
        }


    // If the option is unrecognised...
    }catch (po::error &ex){
        std::cerr << ex.what() << std::endl;
        return ERROR_IN_CMD_LINE;
    }
}
