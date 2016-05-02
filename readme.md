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

    TANT QUE non timeout FAIRE
        -- Une nouvelle tâche arrive
        SI aucun processeur ne peut contenir la tâche
            Attendre qu'un processeur se libère
        SINON
            SI un processeur est vide (pas de tâches en cours)
                lui attribuer automatiquement la tâche.
            SINON
                Récupérer le processeur le moins utilisé
                Lui assigner la tâche
            FINSI
        FINSI
    FIN TQ