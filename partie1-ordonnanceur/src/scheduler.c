#include <stdio.h>
#include "../include/scheduler.h"

void executer_simulation(int politique_choisie, Processus *procs, int count) {
    // On trie toujours par date d'arrivée avant de simuler
    trier_par_arrivee(procs, count);
    
    switch (politique_choisie) {
        case 1:
            politique_fifo(procs, count);
            break;
        case 2:
            politique_sjf(procs, count);
            break;
        case 3:
            politique_rr(procs, count);
            break;
        default:
            printf("[Erreur] Politique inconnue.\n");
    }
}