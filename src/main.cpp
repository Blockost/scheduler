#include <omp.h>
#include "main.h"

namespace po = boost::program_options;

int main(int argc, char **argv) {

    po::options_description desc("Options");
    po::variables_map vm;

    std::string queue_name = "scheduler_queue";
    std::string filepath = "logs";

    int ncores = omp_get_num_procs();

    // Define all available options
    desc.add_options()
            ("help,h", "Print this help message")
            ("client,c", "Start the client to populate the queue")
            ("sequential,s", "Launch the scheduler in sequential mode")
            ("parallel,p", "Launch the scheduler in parallel mode")
            ("distrib,d", "Launch the scheduler in distributed mode");

    try {

        // Parse options in cmd line
        po::store(po::parse_command_line(argc, argv, desc), vm);

        /* Help option */
        if (vm.count("help")) {
            std::cout << desc;
        }

        /* Launch the client */
        if (vm.count("client")) {
            Client client{queue_name};
            client.start();

        }

        /* Launch sched in sequential mode */
        if (vm.count("sequential")) {
            SequentialScheduler seq_sched{queue_name, filepath, ncores};
            seq_sched.start();
        }

        /* Launch sched in parallel mode */
        if (vm.count("parallel")) {
            ParallelScheduler parallel_sched{queue_name, filepath, ncores};
            parallel_sched.start();
        }


        // If the option is unrecognised...
    } catch (po::error &ex) {
        std::cerr << ex.what() << std::endl;
        return ERROR_IN_CMD_LINE;
    }
}
