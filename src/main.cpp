#include <iostream>
#include <vector>
#include <fstream>
#include <json/json.h>
#include <bits/stl_list.h>

#include "Task.h"

using namespace std;

int main() {

    vector<Task> pool;

    pool.push_back(Task("éééé", 500));
    pool.push_back(Task("lala", 500));
    pool.push_back(Task("toto", 100));

    //#pragma omp parallel
    {
        // Code inside this region runs in parallel.
        cout << "Hello\n";

        for(Task& task : pool){
            task.execute();
        }
    }

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
