#ifndef TAD_H
#define TAD_H

struct No No;

typedef struct Baralho Baralho;

Baralho criar (int n);

void limpa (Baralho *baralho, int n);

int corta (Baralho *b);

int sobe (Baralho *b);

int vira (Baralho *b);

int vira_topo (Baralho *b, int k);

int pos_carta (Baralho *b, int p);

int sobe (Baralho *b, int x);

void mostra (Baralho *b);

#endif