# Gestionnaire d'Arborescence de Fichier

## Description :
Ce projet vise à développer un programme capable de simuler les instructions système de manipulation de l'arborescence des dossiers et fichiers. Le programme fonctionnera en lisant une liste d'instructions à partir d'un fichier d'entrée et en simulant ces instructions pour manipuler une structure d'arbre stockée en mémoire.

## Fonctionnalités
- **Navigation** : Le programme peut se déplacer à travers l'arborescence de dossiers/fichiers, permettant l'accès aux différents niveaux et éléments.
- **Création** : Il est possible de créer de nouveaux dossiers et fichiers à n'importe quel emplacement dans l'arborescence.
- **Déplacement** : Les dossiers et fichiers peuvent être déplacés d'un endroit à un autre, permettant une réorganisation flexible.
- **Copie** : Le programme peut copier des dossiers ou fichiers, facilitant la duplication des éléments.
- **Suppression** : Les dossiers et fichiers inutiles peuvent être supprimés de l'arborescence.
- **Afficher** : Le programme peut afficher le répertoire courant mais egalement toutes l'arborescence.

## Comment ça fonctionne
Le programme lit un fichier contenant qui doit contenir : cp ; mv ; cd ; touch ; rm ; print ; ls ; mkdir. Sans options.
Avec les chemain ecrit : nomDossier/nomDossier2/Fichier ou nomDossier/nomDossier2 . Sans espace et sans /. et /..
Il doit avoir une instruction, un appel de commande par ligne une séquence d'instructions (touch,mkdir,mv,). 

## Utilisation
Préparation de la liste d'instructions : Créez un fichier texte contenant les instructions à exécuter, chacune sur une nouvelle ligne.
Exécution du programme : make 
                        ./program nom_fic
                                             

