#include <stdio.h>
#include <stdbool.h>
#include "../include/scheduler.h"

#define QUANTUM 2

void politique_rr(Processus *procs, int count) {
    printf("\n=== Lancement de la politique: Round-Robin (RR, Quantum = %d) ===\n", QUANTUM);
    
    int temps_actuel = 0;
    int completes = 0;
    
    // Réinitialisation des temps restants
    for(int i = 0; i < count; i++) {
        procs[i].temps_restant = procs[i].duree_cpu;
    }

    while (completes < count) {
        bool idle = true;

        for (int i = 0; i < count; i++) {
            if (procs[i].date_arrivee <= temps_actuel && procs[i].temps_restant > 0) {
                idle = false;
                int temps_execution = (procs[i].temps_restant > QUANTUM) ? QUANTUM : procs[i].temps_restant;
                
                printf("[Temps %d] Execution de %s pendant %d (Restant: %d)\n", 
                       temps_actuel, procs[i].nom, temps_execution, procs[i].temps_restant - temps_execution);
                
                temps_actuel += temps_execution;
                procs[i].temps_restant -= temps_execution;

                if (procs[i].temps_restant == 0) {
                    completes++;
                    printf("[Temps %d] -> Processus %s TERMINE.\n", temps_actuel, procs[i].nom);
                }
            }
        }

        if (idle) {
            printf("[Temps %d] CPU au repos (Idle)\n", temps_actuel);
            temps_actuel++;
        }
    }
    printf("Fin de la simulation Round-Robin. Temps total: %d\n", temps_actuel);
}