#include "parallel_sched.h"

using namespace std;

void launch_parallel(void){

    cout << "Launching scheduler in parallel mode..." << endl;

    /*double start_time = omp_get_wtime();

    // Execute tasks
    #pragma omp parallel
    #pragma omp single
    {
        for(auto it = pool.begin(); it != pool.end(); ++it){
            #pragma omp task firstprivate(it)
            it->execute();
        }
        #pragma omp taskwait
    }

    double end_time = omp_get_wtime();

    cout << "All tasks executed in " << end_time - start_time << "s" << endl;*/
}


