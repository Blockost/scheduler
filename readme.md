#Readme 

## Populating 

Use -c or --client as argument on the scheduler's executable to start the client. It will populate the queue with your tasks.

## Scheduling

User -s or --sequential to start the scheduler in sequential mode. User -p or --parallel to start in parallel.

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
