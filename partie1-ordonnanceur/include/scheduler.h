#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef struct {
    char nom[50];
    int date_arrivee;
    int duree_cpu;
    int temps_restant; // Ajouté pour Round-Robin
} Processus;

// Point d'entrée de l'orchestration
void executer_simulation(int politique_choisie, Processus *procs, int count);

// Prototypes des politiques d'ordonnancement
void politique_fifo(Processus *procs, int count);
void politique_sjf(Processus *procs, int count);
void politique_rr(Processus *procs, int count);

// Fonctions utilitaires
int parser_fichier(const char* nom_fichier, Processus* procs);
void trier_par_arrivee(Processus *procs, int count);
void afficher_liste_processus(Processus *procs, int count);

#endif