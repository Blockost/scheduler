#Readme 

CdC -> 21/03/2016 23h59
    Arel + GitLAB
    
## Links

* [Introducing to OpenMP library](http://bisqwit.iki.fi/story/howto/openmp/)
* [Docs about DateTime library of Boost](http://www.boost.org/doc/libs/1_38_0/doc/html/date_time/posix_time.html#date_time.posix_time.time_duration)
* [Assign process to cpu](http://man7.org/linux/man-pages/man2/sched_setaffinity.2.html)

## Basic scheduler

* Generate a task pool
* For each thread worker (basically, one per processor)
* Fetch a task in the pool (also remove it from the pool)
* execute the task
* wait until a task is available
* When the pool is empty, stop the program
* Enhancements : /!\ Competition /!\ - Load-Balancing