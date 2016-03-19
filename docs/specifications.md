# Cahier des charges

## Table des matières
* Introduction
* Specs
* How to implement
* Enhancements
* Conclusion

## Introduction
### Définition du sujet
Dans le cadre du Projet GSI de seconde année d'ingénieur, nous réaliserons un _scheduler_ permmettant d'odonnancer 
différents processus selon plusieur stratégies. Le projet devra s'effectuer par groupe de 3 personnes. L'équipe sera donc constituée de ESPIGOLE Simon, GILBERT Teddy et LEGRAND Hugo.

### Objectif
L'objectif sera pour nous de réaliser ce projet avec rigueur, du code commenté et documenté. Nous essaierons de développer
une application rapide et efficace, avec le plus de fonctionalités supplémentaires possibles.

## Specs
Qu'est qu'un scheduler ? 
Comme expliqué par le client, le but du projet est de récuperer une file d'attente avec de multiples tâches à rediriger.
La redirection doit se faire en fonction de l'importance ou de la taille de la tâche.
Toutes ces tâches se verront attribuer une partie d'un core de CPU afin de l'effectuer.

## How to implement
Pour implémenter ce _scheduler_, nous utiliserons le C++, avec les librairies OpenMP et MPI. Les connections réseau
seront faites en IPv6,  et le code source sera partagé sur le GitLAB de l'École. Notre groupe utilisera l'environnement 
de développement __CLion__ (JetBrains) pour toute la rédaction du code source, ainsi que le partage.

## Enhancements
S'il nous reste du temps après avoir implémenté les principales fonctionnalités, nous choisirons de développer une 
interface de commande un peu plus développée en premier lieu. Nous pourrons par la suite gérer un peu mieux les ressources
en instaurant un _timeout_ pour toutes les tâches gérées, qui seront tuées si elles dépassent ce laps de temps. Puis une 
hiérarchisation des tâches sera effectuée : des priorités seront assignées aux tâches et les plus importantes seront 
exécutées en premier.

## Conclusion
* To conclude ? Really...?