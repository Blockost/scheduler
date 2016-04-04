#include <iostream>
#include <vector>
#include <fstream>
#include <json/json.h>
#include <bits/stl_list.h>

#include "Task.h"
#include "boost/program_options.hpp"
#include "flags.h"


using namespace std;
namespace po = boost::program_options;

void func(void){
    cout << "Func called !";
}

int main(int argc, char** argv) {

    string filename = "tasks.json";
    po::options_description desc("Options");
    po::variables_map vm;

    // Define all available options
    desc.add_options()
            ("help,h", "Print this help message")
            ("include-file,i", po::value<string>(), "Specify the file to include. If not specified, it will be parsed the file \"tasks.json\""
                    "at the executable's location")
            ("seq,s", "Launch the scheduler in sequential mode")
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
        /*if(vm.count("i")){ cout << "specified file : " << vm["i"].as() << endl;
        }*/


    // If the option is unrecognised...
    }catch (po::error &e){
        cerr << e.what() << endl;
        return ERROR_IN_CMD_LINE;
    }




    string json_example = "{\"array\": \
                            [\"item1\", \
                            \"item2\"], \
                            \"not an array\": \
                            \"asdf\" \
                         }";

    /*Json::Value root;
    Json::Reader reader;

    bool parseSuccess = reader.parse(json_example, root, false);*/



    /*vector<Task> pool;

    pool.push_back(Task("éééé", 500));
    pool.push_back(Task("lala", 500));
    pool.push_back(Task("toto", 100));

    #pragma omp parallel
    {
        // Code inside this region runs in parallel.
        cout << "Hello\n";

        for(Task& task : pool){
            task.execute();
        }
    }*/



    /*
     * Generate a task pool
     * For each thread worker (basically, one per processor)
     *      Fetch a task in the pool (also remove it from the pool)
     *      execute the task
     *      wait until a task is available
     ******
     * When the pool is empty, stop the program
     *
     *      Enhancements : /!\ Competition /!\ - Load-Balancing
     */

    Json::Value root;
    Json::Reader reader;


    Json::Value task;
    std::ifstream people_file("TESTNAME.json", std::ifstream::binary);
    people_file >> task;

    cout<<task<< endl; //This will print the entire json object.


    Json::Value::const_iterator iterator1;

    for(iterator1 = task.begin(); iterator1 != task.end(); iterator1++)
    {
        cout << task[iterator1.name()]["name"] << " --- ";
        cout << task[iterator1.name()]["duration"] << endl;
    }


}
