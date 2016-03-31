#include <iostream>
#include <vector>

#include "Task.h"

using namespace std;
int main() {

    vector<Task> pool;

    pool.push_back(Task("Task1", new time_duration(0,2,3,4)));
    pool.push_back(Task("Task2", new time_duration(0,2,0,5)));
    pool.push_back(Task("Task3", new time_duration(0,0,3,100)));

    //#pragma omp parallel
    {
        // Code inside this region runs in parallel.
        cout << "Hello\n";

        for(Task& task : pool){
            task.execute();
        }
    }

}

