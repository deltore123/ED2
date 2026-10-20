#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

struct No {
    int rotulo;
    struct No *proximo;
    struct No *anterior;
};

struct Baralho {
    No *sentinela;
};

Baralho *criar (int n){
    Baralho *b = malloc(sizeof(Baralho));
    if (b==NULL){
        return NULL;
    }
    b->sentinela = malloc(sizeof(No));
    if (b->sentinela == NULL) {
        free(b);
        return NULL;
    }
    b->sentinela->rotulo = -1;
    b->sentinela->proximo = b->sentinela;
    b->sentinela->anterior = b->sentinela;
    No *atual = b->sentinela;
    for (int i=1; i<=n; i++){
        atual->proximo = malloc(sizeof(No));
        if (atual->proximo == NULL){
            return NULL;
        }
        atual->proximo->rotulo = i;
        atual->proximo->anterior=atual;
        atual= atual->proximo;
    }
    b->sentinela->anterior = atual;
    atual->proximo = b->sentinela;
    return b;
}

void limpa (Baralho *baralho){
    if (baralho == NULL){
        return;
    }
    if (baralho->sentinela == NULL){
        free(baralho);
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

int corta (Baralho *b, int n){
    if (b == NULL || b->sentinela== NULL){
        return 0;
    }
    No *atual = b->sentinela->proximo;
    while (atual!=b->sentinela && atual->rotulo != n){
        atual = atual->proximo;
    }
    if (atual == b->sentinela){
        return 0;
    }
    atual=atual->proximo;
    b->sentinela->proximo = atual;
    b->sentinela->anterior->proximo = atual->anterior;
    atual->anterior->proximo = b->sentinela;
    atual->anterior = b->sentinela;
    return 1;
}

int sobe (Baralho *b, int n){
    if (b == NULL || b->sentinela== NULL){
        return 0;
    }
    No *atual = b->sentinela->proximo;
    while (atual!=b->sentinela && atual->rotulo != n){
        atual = atual->proximo;
    }
    if (atual == b->sentinela){
        return 0;
    }
    if (atual == b->sentinela->anterior){
        return 1;
    }
    atual->anterior->proximo = atual->proximo;
    atual->proximo->anterior = atual->anterior;
    atual->proximo = b->sentinela;
    atual->anterior = b->sentinela->anterior->anterior;
    b->sentinela->anterior->proximo = atual;
    b->sentinela->anterior = atual;
    return 1;
}

int vira (Baralho *b){
    if (b==NULL || b->sentinela->proximo == NULL){
        return 0;
    }
    No *p = b->sentinela->proximo;
    b->sentinela->proximo = b->sentinela->anterior;
    b->sentinela->anterior = p;
    p= p->proximo;
    No *aux;
    while (p!=b->sentinela){
        aux = p->proximo;
        p->proximo = p->anterior;
        p->anterior = aux;
        p = p->anterior;
    }
    return 1;
}

int vira_topo(Baralho *b, int k) {
    if (b == NULL || b->sentinela == NULL)
        return 0;

    No *s = b->sentinela;
    No *atual = s->proximo;

    while (atual != s && atual->rotulo != k)
        atual = atual->proximo;

    if (atual == s)
        return 0;

    if (atual == s->anterior)
        return 1;

    No *topo = s->anterior;
    No *base = atual->anterior;

    No *p = topo;
    No *aux;

    while (p != atual) {
        aux = p->proximo;
        p->proximo = p->anterior;
        p->anterior = aux;
        p = aux;
    }
    s->anterior = base;
    base->proximo = s;

    topo->anterior = atual;
    atual->proximo = topo;

    return 1;
}

int pos_carta (Baralho *b, int p){
    int contador= 0;
    if (b==NULL || b->sentinela->proximo == b->sentinela){
        return 0;
    }
    No *atual = b->sentinela->proximo;
    while (atual!=b->sentinela && atual->rotulo != p){
        atual = atual->proximo;
        contador++;
    }
    if (atual == b->sentinela){
        return 0;
    }
    else {
        return contador;
    }
    
}



void mostra (Baralho *b){
    if (b==NULL || b->sentinela->proximo == b->sentinela){
        return;
    }
    No *atual = b->sentinela->anterior;
    while (atual != b->sentinela){
        printf ("%d", atual->rotulo);
        atual = atual->anterior;
        if (atual ->proximo == b->sentinela){
            printf("%d", atual->rotulo);
            return;
        }
    }
}


