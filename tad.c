#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

struct No {
    int rotulo;
    struct No *proximo;
    struct No *anterior;
}



struct Baralho {
    No *sentinela;
};

Baralho criar (int n){
    Baralho *b = malloc(sizeof(Baralho));
    if (b==NULL){
        return NULL;
    }
    b->sentinela = malloc(sizeof(No));
    No *atual = sentinela;
    for (int i=1; i<=n; i++){
        atual->proximo = malloc(sizeof(No));
        if (atual->proximo == NULL){
            return NULL;
        }
        atual->proximo.rotulo = n;
        atual->proximo->anterior=atual;
        atual= atual->proximo;
    }
    b->sentinela->anterior = atual;
    atual->proximo = b->sentinela;
    sentinela->rotulo = -1;
    return b;
}

void limpa (Baralho *baralho, int n){
    if (baralho == NULL){
        return;
    }
    No *atual = baralho->sentinela->proximo;
    No *proximo = atual->proximo->proximo;
    while (proximo != baralho->sentinela){
        free(atual);
        atual = proximo;
        proximo = proximo->proximo;
    }
    free (atual);
    free(baralho->sentinela);
    free(baralho);
}

int corta (Baralho *b);

int sobe (Baralho *b);

int vira (Baralho *b);

int vira_topo (Baralho *b, int k);

int pos_carta (Baralho *b, int p);

int sobe (Baralho *b, int x);

void mostra (Baralho *b);


