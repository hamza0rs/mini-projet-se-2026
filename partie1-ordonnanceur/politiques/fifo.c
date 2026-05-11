#include <stdio.h>
#include "../include/scheduler.h"

void politique_fifo(Processus *procs, int count) {
    printf("\n=== Lancement de la politique: FIFO ===\n");
    int temps_actuel = 0;
    
    for(int i = 0; i < count; i++) {
        if(temps_actuel < procs[i].date_arrivee) {
            temps_actuel = procs[i].date_arrivee;
        }
        printf("[Temps %d] Execution du processus %s (Duree: %d)\n", 
               temps_actuel, procs[i].nom, procs[i].duree_cpu);
        temps_actuel += procs[i].duree_cpu;
    }
    printf("Fin de l'ordonnancement. Temps d'execution total: %d unites.\n", temps_actuel);
}