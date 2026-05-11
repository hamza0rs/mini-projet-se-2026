CC=gcc
CFLAGS=-Wall -pthread -I./include

all: build_dir serveur_outils client_bras

build_dir:
	mkdir -p build

serveur_outils: serveur/gestionnaire_outils.c
	$(CC) $(CFLAGS) -o build/serveur_outils serveur/gestionnaire_outils.c

client_bras: client/bras_robotique.c
	$(CC) $(CFLAGS) -o build/client_bras client/bras_robotique.c

clean:
	rm -rf build/