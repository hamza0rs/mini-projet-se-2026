# Document de Conception & Compilation

## Processus de construction
Ce projet utilise des Makefiles séparés pour la partie 1 et la partie 2.
- Pour compiler l'ordonnanceur : `cd partie1-ordonnanceur && make`
- Pour compiler la simulation d'entrepôt : `cd partie2-bras-robotiques && make`

## Format du répertoire des politiques d'ordonnancement
Le répertoire `politiques/` contient le code source de chaque politique (FIFO, SJF, RR). Chaque fichier définit un point d'entrée unique qui respecte la signature définie dans `include/scheduler.h`.