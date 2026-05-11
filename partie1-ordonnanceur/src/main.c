#include <stdio.h>
#include <stdlib.h>
#include "../include/scheduler.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <tests/config_exemple.txt>\n", argv[0]);
        return 1;
    }

    Processus procs[100];
    int count = parser_fichier(argv[1], procs);
    if (count <= 0) {
        printf("[Erreur] Aucun processus charge valide. Sortie.\n");
        return 1;
    }

    afficher_liste_processus(procs, count);

    int choix;
    do {
        printf("\n--- Menu Ordonnanceur ---\n");
        printf("1. FIFO\n");
        printf("2. SJF\n");
        printf("3. Round-Robin (RR)\n");
        printf("0. Quitter\n");
        printf("Choisissez une politique : ");
        if (scanf("%d", &choix) != 1) break;

        if (choix >= 1 && choix <= 3) {
            executer_simulation(choix, procs, count);
        } else if (choix != 0) {
            printf("Choix invalide.\n");
        }
    } while(choix != 0);

    return 0;
}