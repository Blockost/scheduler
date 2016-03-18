# Cahier des charges 

## Introduction
* Définition du sujet
* Objectif

## Specs
* Faut faire quoi concrétement ?

## How to implement ?
* Comment on va le faire ?
* Pour implémenter ce _scheduler_, nous utiliserons le C++, avec les librairies OpenMP et MPI. Les connections réseau
seront faites en IPv6,  et le code source sera partagé sur le GitLAB de l'École. Notre groupe utilisera l'environnement 
de développement CLion (JetBrains) pour toute la rédaction du code source, ainsi que le partage.

## Enhancements ?
* S'il nous reste du temps après avoir implémenté les principales fonctionnalités, nous choisirons de développer une 
interface de commande un peu plus développée en premier lieu. Nous pourrons par la suite gérer un peu mieux les ressources
en instaurant un _timeout_ pour toutes les tâches gérées, qui seront tuées si elles dépassent ce laps de temps. Puis une 
hiérarchisation des tâches sera effectuée : des priorités seront assignées aux tâches et les plus importantes seront 
exécutées en premier.

## Conclusion
* To conclude ? Really...?