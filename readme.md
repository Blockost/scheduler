#Readme 

CdC -> 21/03/2016 23h59
    Arel + GitLAB
    
## Links

* [Introducing to OpenMP library](http://bisqwit.iki.fi/story/howto/openmp/)
* [Docs about DateTime library of Boost](http://www.boost.org/doc/libs/1_38_0/doc/html/date_time/posix_time.html#date_time.posix_time.time_duration)
* [Assign process to cpu](http://man7.org/linux/man-pages/man2/sched_setaffinity.2.html)

## Populating 

User --server as argument on ProjetGSI executable to start the server. It will populate the queue with your tasks

## Scheduling

La charge des processeurs est compris entre 0 et 1. Les taches utilisent des fractions de CPU comme indice de charge. 
Par exemple, 0.1CPU, 0.25CPU, 0.9CPU


### Sequential

    SI aucun processeur ne peut contenir la tache
        Attendre qu'un processeur se libère
        -- OU --
        Supprimer l'une des tâches suivant une strat' particulière
    SINON
        SI un processeur est libre (pas de tâches en cours)
            lui attribuer automatiquement la tâche.
        SININ
            Attribuer la tache au processeur le moins utilisé
        FINSI
    FINSI
            
            
### Parallel - Single Machine (OpenMP)

### Parallel - Multi Machines (MPI)
