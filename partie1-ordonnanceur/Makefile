CC=gcc
CFLAGS=-Wall -I./include

# Trouver tous les fichiers .c
SRC=$(wildcard src/*.c)
POLITIQUES=$(wildcard politiques/*.c)
OBJ=$(SRC:.c=.o) $(POLITIQUES:.c=.o)

EXEC=ordonnanceur

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o politiques/*.o $(EXEC)