#ifndef TAD_H
#define TAD_H

typedef struct No No;

typedef struct Baralho Baralho;

Baralho *criar (int n);

void limpa (Baralho *baralho);

int corta (Baralho *b, int n);

int sobe (Baralho *b, int n);

int vira (Baralho *b);

int vira_topo (Baralho *b, int k);

int pos_carta (Baralho *b, int p);

void mostra (Baralho *b);

int carta (Baralho *b, int p);

#endif
