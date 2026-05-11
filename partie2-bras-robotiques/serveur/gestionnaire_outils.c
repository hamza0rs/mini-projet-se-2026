#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <time.h>
#include "../include/commun.h"

#define NB_OUTILS 10

// Les verrous de synchronisation pour chaque outil physique
pthread_mutex_t mutex_outils[NB_OUTILS];

void log_message(const char* message) {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("[%s] %s\n", buffer, message);
}

void* gerer_connexion_robot(void* arg) {
    int client_fd = *(int*)arg;
    free(arg);

    char buffer[MAX_BUFFER];
    int read_size;

    while ((read_size = recv(client_fd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[read_size] = '\0';
        char cmd[50];
        int t1, t2;

        sscanf(buffer, "%s %d %d", cmd, &t1, &t2);

        if (strcmp(cmd, CMD_REQUETE) == 0) {
            char log_msg[100];
            sprintf(log_msg, "Demande recue pour les outils %d et %d", t1, t2);
            log_message(log_msg);

            // =======================================================
            // PREVENTION DU DEADLOCK (Option A : Ordre hierarchique fixe)
            // =======================================================
            int premier = (t1 < t2) ? t1 : t2;
            int deuxieme = (t1 < t2) ? t2 : t1;

            sprintf(log_msg, "Acquisition de l'outil %d...", premier);
            log_message(log_msg);
            pthread_mutex_lock(&mutex_outils[premier]);

            sprintf(log_msg, "Acquisition de l'outil %d...", deuxieme);
            log_message(log_msg);
            pthread_mutex_lock(&mutex_outils[deuxieme]);

            log_message("Les deux outils sont verrouilles. Allocation au client.");
            send(client_fd, MSG_ACCORDE, strlen(MSG_ACCORDE), 0);

        } else if (strcmp(cmd, CMD_LIBERER) == 0) {
            // Libération dans l'ordre inverse
            int premier = (t1 < t2) ? t1 : t2;
            int deuxieme = (t1 < t2) ? t2 : t1;

            pthread_mutex_unlock(&mutex_outils[deuxieme]);
            pthread_mutex_unlock(&mutex_outils[premier]);

            log_message("Outils correctement liberes.");
            send(client_fd, MSG_LIBERE_OK, strlen(MSG_LIBERE_OK), 0);
        }
    }

    close(client_fd);
    return NULL;
}

int main() {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Initialisation des verrous de chaque outil
    for (int i = 0; i < NB_OUTILS; i++) {
        pthread_mutex_init(&mutex_outils[i], NULL);
    }

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return -1;
    }

    listen(server_fd, 5);
    log_message("Serveur Central d'Outils demarre. En attente de bras robotiques...");

    while (1) {
        int *new_socket = malloc(sizeof(int));
        *new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        
        log_message("Un bras robotique s'est connecte au réseau.");

        pthread_t client_thread;
        pthread_create(&client_thread, NULL, gerer_connexion_robot, (void*)new_socket);
        pthread_detach(client_thread); // Les ressources du thread sont libérées dès son extinction
    }

    return 0;
}