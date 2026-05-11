#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/scheduler.h"

// Permet de nettoyer les espaces blancs au début d'une ligne
char* trim_left(char *str) {
    while (isspace((unsigned char)*str)) str++;
    return str;
}

int parser_fichier(const char* nom_fichier, Processus* procs) {
    FILE *file = fopen(nom_fichier, "r");
    if (!file) {
        perror("[Parser Error] Impossible d'ouvrir le fichier de configuration");
        return -1;
    }

    char ligne[256];
    int count = 0;

    while (fgets(ligne, sizeof(ligne), file)) {
        char *cleaned = trim_left(ligne);

        // Ignore les commentaires et les lignes vides
        if (cleaned[0] == '\0' || cleaned[0] == '#' || cleaned[0] == '\n' || cleaned[0] == '\r') {
            continue;
        }

        // Extraction des attributs : Nom, Date d'arrivée, Durée CPU
        if (sscanf(cleaned, "%s %d %d", procs[count].nom, &procs[count].date_arrivee, &procs[count].duree_cpu) == 3) {
            procs[count].temps_restant = procs[count].duree_cpu; // Initialise pour Round-Robin
            count++;
        } else {
            fprintf(stderr, "[Parser Warning] Ligne mal formatee ignoree : %s", ligne);
        }
    }

    fclose(file);
    return count;
}