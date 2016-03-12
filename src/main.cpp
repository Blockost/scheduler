#include <iostream>
#include <vector>


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
}
