CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2

# programa principal e gerador em executaveis separados
all: baralho gerador

baralho: main.o tad.o
	$(CC) $(CFLAGS) -o $@ main.o tad.o

gerador: gerador.c
	$(CC) $(CFLAGS) -o $@ gerador.c

main.o: main.c tad.h
	$(CC) $(CFLAGS) -c main.c

tad.o: tad.c tad.h
	$(CC) $(CFLAGS) -c tad.c

clean:
	rm -f *.o baralho gerador

.PHONY: all clean
