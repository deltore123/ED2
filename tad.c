#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

// no da lista duplamente ligada
struct No {
    int rotulo;
    struct No *proximo;
    struct No *anterior;
};

// baralho guarda so a sentinela
// sentinela->proximo e o fundo, sentinela->anterior e o topo
struct Baralho {
    No *sentinela;
};

// cria baralho com cartas de 1 ate n
Baralho *criar (int n){
    Baralho *b = malloc(sizeof(Baralho));
    if (b==NULL){
        return NULL;
    }
    // cria a sentinela que aponta pra si mesma 
    b->sentinela = malloc(sizeof(No));
    if (b->sentinela == NULL) {
        free(b);
        return NULL;
    }
    b->sentinela->rotulo = -1;
    b->sentinela->proximo = b->sentinela;
    b->sentinela->anterior = b->sentinela;
    No *atual = b->sentinela;
    // cria as cartas em ordem
    for (int i=n; i>=1; i--){
        atual->proximo = malloc(sizeof(No));
        // se malloc falhar, libera tudo que foi criado
        if (atual->proximo == NULL) {
        No *p = b->sentinela->proximo;

        while (p != b->sentinela && p != NULL) {
            No *aux = p->proximo;
            free(p);
            p = aux;
        }

    free(b->sentinela);
    free(b);
    return NULL;
}
        atual->proximo->rotulo = i;
        atual->proximo->anterior=atual;
        atual= atual->proximo;
    }
    // fecha o circulo com a sentinela
    b->sentinela->anterior = atual;
    atual->proximo = b->sentinela;
    return b;
}

// libera todas as cartas, a sentinela e o baralho
void limpa (Baralho *baralho){
    if (baralho == NULL){
        return;
    }
    // baralho vazio: libera so sentinela e baralho
    if (baralho->sentinela->proximo == baralho->sentinela){ 
        free(baralho->sentinela);
        free(baralho);
        return;
    }
    No *atual = baralho->sentinela->proximo;
    No *proximo = atual->proximo;
    // libera cada carta guardando a proxima antes
    while (proximo != baralho->sentinela){
        free(atual);
        atual = proximo;
        proximo = proximo->proximo;
    }
    free (atual);
    free(baralho->sentinela);
    free(baralho);
}

// corta o baralho: a carta n vira o topo e as de cima vao para o fundo na mesma ordem
int corta (Baralho *b, int n){
    if (b == NULL || b->sentinela== NULL){
        return 0;
    }
    // procura a carta n
    No *atual = b->sentinela->proximo;
    while (atual!=b->sentinela && atual->rotulo != n){
        atual = atual->proximo;
    }
    // n nao encontrada
    if (atual == b->sentinela){
        return 0;
    }
    // corte no topo nao muda o baralho
    if (atual == b->sentinela->anterior){
        return 1;
    }
    No *topo = b->sentinela->anterior;
    No *fundo = b->sentinela->proximo;
    No *topo_novo = atual;
    // carta seguinte a n vira o novo fundo
    atual->proximo->anterior = b->sentinela;
    b->sentinela->anterior = atual;
    b->sentinela->proximo = atual->proximo;
    atual->proximo = b->sentinela;
    // liga o antigo topo ao antigo fundo
    topo->proximo = fundo;
    fundo->anterior = topo;
    return 1;
}

// move a carta n para o topo
int sobe (Baralho *b, int n){
    if (b == NULL || b->sentinela== NULL){
        return 0;
    }
    // procura a carta n
    No *atual = b->sentinela->proximo;
    while (atual!=b->sentinela && atual->rotulo != n){
        atual = atual->proximo;
    }
    // n nao encontrada
    if (atual == b->sentinela){
        return 0;
    }
    // ja esta no topo
    if (atual == b->sentinela->anterior){
        return 1;
    }
    // tira a carta da posicao atual
    atual->anterior->proximo = atual->proximo;
    atual->proximo->anterior = atual->anterior;
    // coloca a carta no topo
    atual->proximo = b->sentinela;
    atual->anterior = b->sentinela->anterior;
    b->sentinela->anterior->proximo = atual;
    b->sentinela->anterior = atual;
    return 1;
}

// inverte o baralho inteiro
int vira (Baralho *b){
    if (b==NULL || b->sentinela->proximo == NULL){
        return 0;
    }
    No *s = b->sentinela;
    No *p = s->proximo;
    No *aux;
    // troca proximo e anterior de todos os nos, comecando no primeiro
    while (p != s){
        aux = p->proximo;
        p->proximo = p->anterior;
        p->anterior = aux;
        p = aux;
    }
    // troca os ponteiros da sentinela
    aux = s->proximo;
    s->proximo = s->anterior;
    s->anterior = aux;
    return 1;
}

// inverte as k cartas de cima
int vira_topo(Baralho *b, int k) {
    if (b == NULL || b->sentinela == NULL || k < 1)
        return 0;

    No *s = b->sentinela;
    No *topo = s->anterior;
    No *base = topo;

    // anda ate a k-esima carta a partir do topo
    for (int i = 1; i < k && base != s; i++){
        base = base->anterior;
    }

    // k maior que o baralho (ou baralho vazio)
    if (base == s){
        return 0;
    }

    // carta logo abaixo do trecho (pode ser a sentinela)
    No *abaixo = base->anterior;

    // troca proximo e anterior dos k nos
    No *p = topo;
    No *aux;
    for (int i = 0; i < k; i++) {
        aux = p->anterior;
        p->anterior = p->proximo;
        p->proximo = aux;
        p = aux;
    }

    // religa as pontas
    abaixo->proximo = topo;
    topo->anterior = abaixo;
    base->proximo = s;
    s->anterior = base;
    return 1;
}

// retorna a posicao da carta p contando a partir do topo (0 se nao achar)
int pos_carta (Baralho *b, int p){
    int contador = 1;
    if (b==NULL || b->sentinela->proximo == b->sentinela){
        return 0;
    }
    // conta a partir do topo
    No *atual = b->sentinela->anterior;
    while (atual!=b->sentinela && atual->rotulo != p){
        atual = atual->anterior;
        contador++;
    }
    // carta nao encontrada
    if (atual == b->sentinela){
        return 0;
    }
    return contador;
}



// imprime as cartas do topo ate o fundo
void mostra (Baralho *b){
    // baralho vazio, nao imprime nada
    if (b==NULL || b->sentinela->proximo == b->sentinela){
        return;
    }
    No *atual = b->sentinela->anterior;
    while (atual != b->sentinela){
        if (atual -> anterior == b->sentinela || b->sentinela->proximo == atual){
            printf("%d\n", atual->rotulo);
            return;
        }
        printf ("%d ", atual->rotulo);
        atual = atual->anterior;
        if (atual -> anterior == b->sentinela){
            printf("%d\n", atual->rotulo);
            return;
        }
    }
}
//mostra o rotulo da carta na posicao p
int carta (Baralho *b, int p){
    if (b== NULL || b->sentinela->proximo == b->sentinela){
        return -1;
    }
    No *atual = b->sentinela->anterior;
    int contador= 1;
    while (contador != p && atual != b->sentinela){
        atual = atual->anterior;
        contador++;
    }
    if (atual == b->sentinela){
        return -1;
    }
    else {
        return atual->rotulo;
    }
}