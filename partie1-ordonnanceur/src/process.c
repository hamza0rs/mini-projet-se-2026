#include <stdio.h>
#include "../include/scheduler.h"

// Compare deux processus par date d'arrivée (pour le tri de base)
int comparer_arrivee(const void *a, const void *b) {
    Processus *p1 = (Processus *)a;
    Processus *p2 = (Processus *)b;
    return p1->date_arrivee - p2->date_arrivee;
}

void trier_par_arrivee(Processus *procs, int count) {
    qsort(procs, count, sizeof(Processus), comparer_arrivee);
}

void afficher_liste_processus(Processus *procs, int count) {
    printf("\n--- Liste des processus charges ---\n");
    for (int i = 0; i < count; i++) {
        printf("Processus: %s | Arrivee: %d | Duree CPU: %d\n", 
               procs[i].nom, procs[i].date_arrivee, procs[i].duree_cpu);
    }
    printf("-----------------------------------\n");
}