# 🚀 Projet Système d'Exploitation ENSEM 2026

Ce projet d'ingénierie système applique des concepts fondamentaux d'ordonnancement de processus monocœur, de programmation réseau concurrente et de synchronisation de ressources partagées.

---

## 📂 Architecture Modulaire du Projet

Le projet est structuré selon l'arborescence suivante :

```text
mini-projet-se-2026/
├── partie1-ordonnanceur/             # Simulateur d'ordonnancement
│   ├── src/                          # Code principal de l'orchestrateur
│   │   ├── main.c                    # Menu utilisateur et boucle de contrôle
│   │   ├── parser.c                  # Analyseur syntaxique de configuration
│   │   ├── scheduler.c               # Dispatcher d'exécution
│   │   └── process.c                 # Fonctions de gestion de structures
│   ├── politiques/                   # Algorithmes d'ordonnancement séparés
│   │   ├── fifo.c                    # Premier Arrivé, Premier Servi
│   │   ├── sjf.c                     # Plus Court Job en Premier (SJF)
│   │   └── rr.c                      # Tour de Rôle (Round-Robin)
│   ├── include/
│   │   └── scheduler.h               # Entêtes et prototypes de fonctions
│   ├── tests/
│   │   └── config_exemple.txt        # Fichier d'exemple de processus
│   ├── Makefile                      # Système de compilation Partie 1
│   └── README.md                     # Documentation spécifique Partie 1
│
├── partie2-bras-robotiques/          # Simulation d'entrepôt connecté
│   ├── client/
│   │   └── bras_robotique.c          # Client robotique multithreadé
│   ├── serveur/
│   │   └── gestionnaire_outils.c     # Serveur central d'exclusion mutuelle
│   ├── include/
│   │   └── commun.h                  # Protocoles et constantes réseau
│   └── Makefile                      # Système de compilation Partie 2
│
├── docs/
│   └── conception.md                 # Spécifications de build et formatage
├── .gitignore                        # Fichiers ignorés par Git
└── README.md                         # Ce fichier (Guide d'accueil)

## 🎥 Démonstrations Vidéos

Les vidéos de démonstration pas-à-pas du projet sont disponibles en ligne :
* 🖥️ **Partie 1 (Ordonnanceur de processus)** : https://youtu.be/RDoOgWz232Y
* 🤖 **Partie 2 (Simulation de bras robotiques)** : https://youtu.be/YklPbtODt5c
