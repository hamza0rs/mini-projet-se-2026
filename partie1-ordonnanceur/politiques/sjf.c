#include <stdio.h>
#include <stdbool.h>
#include "../include/scheduler.h"

void politique_sjf(Processus *procs, int count) {
    printf("\n=== Lancement de la politique: Shortest Job First (SJF) ===\n");
    
    int temps_actuel = 0;
    int completes = 0;
    bool visite[100] = { false };

    while (completes < count) {
        int index_sjf = -1;
        int min_cpu = 1e9;

        // Trouver le processus arrivé avec le plus court cycle CPU restant
        for (int i = 0; i < count; i++) {
            if (procs[i].date_arrivee <= temps_actuel && !visite[i]) {
                if (procs[i].duree_cpu < min_cpu) {
                    min_cpu = procs[i].duree_cpu;
                    index_sjf = i;
                }
            }
        }

        if (index_sjf != -1) {
            printf("[Temps %d] Execution de %s pendant %d unites.\n", 
                   temps_actuel, procs[index_sjf].nom, procs[index_sjf].duree_cpu);
            temps_actuel += procs[index_sjf].duree_cpu;
            visite[index_sjf] = true;
            completes++;
        } else {
            // Aucun processus n'est encore arrivé, le CPU attend (idle)
            printf("[Temps %d] CPU au repos (Idle)\n", temps_actuel);
            temps_actuel++;
        }
    }
    printf("Fin de la simulation SJF. Temps total: %d\n", temps_actuel);
}