# Cahier des charges

## Table des matières
* Introduction
* Specs
* How to implement
* Enhancements
* Conclusion

## Introduction
### Définition du sujet
Dans le cadre du Projet GSI de seconde année d'ingénieur, nous réaliserons un _scheduler_ permettant d'ordonnancer 
différents processus selon plusieurs stratégies.
### Objectif
L'objectif sera pour nous de réaliser ce projet avec rigueur, du code commenté et documenté. Nous essaierons de développer
une application rapide et efficace, avec le plus de fonctionalités supplémentaires possibles.

## Specs
Comme expliqué par le client, le but du projet est de récuperer une file d'attente avec de multiples tâches à rediriger.
La redirection doit se faire en fonction de la taille de la tâche.
Toutes ces tâches se verront attribuer une partie d'un core de CPU afin de l'effectuer.

## How to implement
Pour implémenter ce _scheduler_, nous utiliserons le C++, avec les librairies OpenMP et MPI. Les connections réseau
seront faites en IPv6,  et le code source sera partagé sur le GitLAB de l'École. Notre groupe utilisera l'environnement 
de développement __CLion__ (JetBrains) pour toute la rédaction du code source, ainsi que le partage.
Pour chaque _thread_ (un par processeur), nous irons chercher une tâche dans le _pool_ de tâches que nous aurons généré 
au préalable, puis nous la supprimerons. Nous exécuterons la tâche, puis attendrons jusqu'à ce que une nouvelle tâche 
soit disponible. Le programme s'arrête lorsqu'il n'y a plus de tâche dans le _pool_ de tâches.

## Enhancements
S'il nous reste du temps après avoir implémenté les principales fonctionnalités, nous choisirons de développer une 
interface de commande un peu plus développée en premier lieu. Nous pourrons par la suite gérer un peu mieux les ressources
en instaurant un _timeout_ pour toutes les tâches gérées, qui seront tuées si elles dépassent ce laps de temps. Puis une 
hiérarchisation des tâches sera effectuée : des priorités seront assignées aux tâches et les plus importantes seront 
exécutées en premier.

## Conclusion
* To conclude ? Really...?