#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include "../include/commun.h"

// Variables de synchronisation entre threads
pthread_mutex_t state_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_network = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_assembly = PTHREAD_COND_INITIALIZER;

typedef enum { STATE_IDLE, STATE_REQUESTING, STATE_READY_TO_ASSEMBLE, STATE_DONE } RobotState;
RobotState current_state = STATE_IDLE;

int sock_fd;
int tool1_id, tool2_id;

// Thread 1: Réflexion (Idle)
void* thread_reflexion(void* arg) {
    printf("[Thread IDLE] Demarrage de la phase de reflexion...\n");
    sleep(2); // Simulation du calcul de trajectoire
    
    pthread_mutex_lock(&state_mutex);
    current_state = STATE_REQUESTING;
    printf("[Thread IDLE] Reflexion terminee. Signalisation de la requete reseau.\n");
    pthread_cond_signal(&cond_network);
    pthread_mutex_unlock(&state_mutex);
    
    return NULL;
}

// Thread 2: Requêtes réseau via Sockets TCP
void* thread_communication(void* arg) {
    char buffer[MAX_BUFFER];

    pthread_mutex_lock(&state_mutex);
    while (current_state < STATE_REQUESTING) {
        pthread_cond_wait(&cond_network, &state_mutex);
    }
    pthread_mutex_unlock(&state_mutex);

    printf("[Thread RESEAU] Envoi de la requete pour outils (%d et %d) au serveur...\n", tool1_id, tool2_id);
    sprintf(buffer, "%s %d %d", CMD_REQUETE, tool1_id, tool2_id);
    send(sock_fd, buffer, strlen(buffer), 0);

    // Attente de l'approbation du serveur
    memset(buffer, 0, sizeof(buffer));
    int valread = recv(sock_fd, buffer, sizeof(buffer) - 1, 0);
    if (valread > 0 && strcmp(buffer, MSG_ACCORDE) == 0) {
        printf("[Thread RESEAU] Succes! Outils accordes par le serveur.\n");
        
        pthread_mutex_lock(&state_mutex);
        current_state = STATE_READY_TO_ASSEMBLE;
        pthread_cond_signal(&cond_assembly);
        pthread_mutex_unlock(&state_mutex);
    } else {
        printf("[Thread RESEAU] Erreur de reception ou refus du serveur.\n");
    }

    return NULL;
}

// Thread 3: Exécution de l'assemblage
void* thread_assemblage(void* arg) {
    pthread_mutex_lock(&state_mutex);
    while (current_state < STATE_READY_TO_ASSEMBLE) {
        pthread_cond_wait(&cond_assembly, &state_mutex);
    }
    pthread_mutex_unlock(&state_mutex);

    printf("[Thread ASSEMBLAGE] Lancement de l'assemblage physique de l'objet...\n");
    sleep(3); // Simulation de l'action de montage de l'objet
    printf("[Thread ASSEMBLAGE] Assemblage physique complete!\n");

    // Libération des outils suite à l'assemblage
    char buffer[MAX_BUFFER];
    sprintf(buffer, "%s %d %d", CMD_LIBERER, tool1_id, tool2_id);
    send(sock_fd, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock_fd, buffer, sizeof(buffer) - 1, 0);
    if (strcmp(buffer, MSG_LIBERE_OK) == 0) {
        printf("[Thread ASSEMBLAGE] Outils rendus libres et disponibles.\n");
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <id_outil_1> <id_outil_2>\n", argv[0]);
        return 1;
    }
    tool1_id = atoi(argv[1]);
    tool2_id = atoi(argv[2]);

    struct sockaddr_in serv_addr;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("[Client Error] Connection echouee");
        return -1;
    }

    printf("🤖 Client Bras Robotique connecte avec succes au serveur central!\n");

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, thread_reflexion, NULL);
    pthread_create(&t2, NULL, thread_communication, NULL);
    pthread_create(&t3, NULL, thread_assemblage, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    close(sock_fd);
    return 0;
}