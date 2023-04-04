CFLAGS=-std=c17 -pedantic -Wall -Wextra -D_DEFAULT_SOURCE -I./include -g -Wno-missing-field-initializers
LDLIBS=-lMLV -lm
CC=clang

all: QuadTree

QuadTree: Main.o Moteur.o Entree_Sortie.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

Main.o: src/Main.c
	$(CC) $(CFLAGS) -c -o $@ $<

Moteur.o: src/Moteur.c
	$(CC) $(CFLAGS) -c -o $@ $<

Entree_Sortie.o : src/Entree_Sortie.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o

mrproper: clean
	rm -f QuadTree