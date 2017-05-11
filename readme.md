#Readme

## Documentation

A special Doxygen documentation has been written for this project. You can read it as html by going to `$PROJECT_ROOT/docs/html/index.html`.
You can also build your own documentation using the latex sources at `$PROJECT_ROOT/docs/latex`.

## Prerequisite

In order to compile and run this project you must have installed on your computer the followings : CMake, Boost, OpenMP

    # apt-get install cmake libboost-all-dev libopenmpi1.6

## Compile sources

To compile sources, you will have to run the following lines :

    $ mkdir bin && cd bin && cmake .. && make
    
It will create a folder name 'bin', navigate to it, build the Makefile, and run the Makefile.

## Populating 

Use -c or --client as argument on the scheduler's executable to start the client. It will populate the queue with your tasks.

    $ ./Scheduler -c

## Scheduling

Use -s or --sequential to start the scheduler in sequential mode. Use -p or --parallel to start in parallel.

    $ ./Scheduler -s

### Algorithm

    WHILE timer not expired DO
        -- New task incoming...
        IF no processor can handle it (processors would be overloaded)
            Wait for a processor to unload
        ELSE
            IF one processor is empty (no task running)
                Attach the task to it
            ELSE
                Get the less-loaded processor
                Attach task to it
            END
        END
    END
