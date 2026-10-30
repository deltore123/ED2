#ifndef TAD_H
#define TAD_H

typedef struct No No;

typedef struct Baralho Baralho;

// tipos do historico (definidos no tad.c)
typedef struct Registro Registro;

typedef struct Historico Historico;

// cria o historico vazio com a capacidade dada (NULL se falhar)
Historico *hist_criar (int capacidade);

// libera o historico
void hist_limpa (Historico *h);

// guarda um registro; se estiver cheio, o mais antigo some
void hist_push (Historico *h, Registro r);

// tira o registro mais recente (0 se o historico estiver vazio)
int hist_pop (Historico *h, Registro *r);

Baralho *criar (int n);

void limpa (Baralho *baralho);

void corta (Baralho *b, int n);

void sobe (Baralho *b, int n);

void vira (Baralho *b);

void vira_topo (Baralho *b, int k);

int pos_carta (Baralho *b, int p);

void mostra (Baralho *b);

int carta (Baralho *b, int p);

// desfaz a operacao mais recente do historico (ultimas 100)
// historico vazio: nao faz nada. o proprio desfaz nao entra no historico
void desfaz (Baralho *b);

#endif