#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

// no da lista duplamente ligada
struct No {
    int rotulo;
    struct No *proximo;
    struct No *anterior;
};

// registro de uma operacao que alterou o baralho
struct Registro {
    char tipo;   // 'C' = CORTA, 'S' = SOBE, 'V' = VIRA, 'T' = VIRATOPO
    int arg;     // CORTA: antigo topo; SOBE: x; VIRATOPO: k
    int pos;     // SOBE: posicao original de x
};

// historico: buffer circular com as operacoes mais recentes
struct Historico {
    Registro *v;
    int capacidade;
    int inicio;   // indice do registro mais antigo
    int qtd;      // quantos registros existem agora
};

// baralho guarda a sentinela, o historico e a flag de invertido
// sem inverter: sentinela->proximo e o fundo, sentinela->anterior e o topo
// e "proximo" anda para cima. invertido troca os papeis dos dois ponteiros,
// entao o VIRA so troca a flag
struct Baralho {
    No *sentinela;
    Historico *hist;
    int invertido;
};

// ponteiro do no p que aponta para a carta de cima (na sentinela: o fundo)
No **cima (Baralho *b, No *p){
    return b->invertido ? &p->anterior : &p->proximo;
}

// ponteiro do no p que aponta para a carta de baixo (na sentinela: o topo)
No **baixo (Baralho *b, No *p){
    return b->invertido ? &p->proximo : &p->anterior;
}

// cria o historico vazio com a capacidade dada
Historico *hist_criar (int capacidade){
    Historico *h = malloc(sizeof(Historico));
    if (h == NULL){
        return NULL;
    }
    h->v = malloc(capacidade * sizeof(Registro));
    if (h->v == NULL){
        free(h);
        return NULL;
    }
    h->capacidade = capacidade;
    h->inicio = 0;
    h->qtd = 0;
    return h;
}

// libera o historico
void hist_limpa (Historico *h){
    if (h == NULL){
        return;
    }
    free(h->v);
    free(h);
}

// guarda um registro; se estiver cheio, a mais antiga some
void hist_push (Historico *h, Registro r){
    if (h->qtd == h->capacidade){
        h->v[h->inicio] = r;
        h->inicio = (h->inicio + 1) % h->capacidade;
    } else {
        h->v[(h->inicio + h->qtd) % h->capacidade] = r;
        h->qtd++;
    }
}

// tira o registro mais recente (0 se o historico estiver vazio)
int hist_pop (Historico *h, Registro *r){
    if (h->qtd == 0){
        return 0;
    }
    h->qtd--;
    *r = h->v[(h->inicio + h->qtd) % h->capacidade];
    return 1;
}

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
    b->invertido = 0;
    b->sentinela->rotulo = -1;
    b->sentinela->proximo = b->sentinela;
    b->sentinela->anterior = b->sentinela;
    // cria o historico (guarda as 100 operacoes mais recentes)
    b->hist = hist_criar(100);
    if (b->hist == NULL) {
        free(b->sentinela);
        free(b);
        return NULL;
    }
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

    hist_limpa(b->hist);
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
        hist_limpa(baralho->hist);
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
    hist_limpa(baralho->hist);
    free(baralho->sentinela);
    free(baralho);
}

// corta o baralho: a carta n vira o topo e as de cima vao para o fundo na mesma ordem
void corta_sem_reg (Baralho *b, int n){
    if (b == NULL || b->sentinela== NULL){
        return;
    }
    // procura a carta n
    No *s = b->sentinela;
    No *atual = *cima(b, s);
    while (atual!=s && atual->rotulo != n){
        atual = *cima(b, atual);
    }
    // n nao encontrada
    if (atual == s){
        return;
    }
    // corte no topo nao muda o baralho
    if (atual == *baixo(b, s)){
        return;
    }
    No *topo = *baixo(b, s);
    No *fundo = *cima(b, s);
    // carta logo acima de n vira o novo fundo
    No *acima = *cima(b, atual);
    *baixo(b, acima) = s;
    *baixo(b, s) = atual;
    *cima(b, s) = acima;
    *cima(b, atual) = s;
    // liga o antigo topo ao antigo fundo
    *cima(b, topo) = fundo;
    *baixo(b, fundo) = topo;
}

// move a carta n para o topo
// devolve a posicao original da carta (0 se nao achar), usada pelo desfaz
int sobe_sem_reg (Baralho *b, int n){
    if (b == NULL || b->sentinela== NULL){
        return 0;
    }
    // procura a carta n a partir do topo, contando a posicao na mesma passada
    No *s = b->sentinela;
    No *topo = *baixo(b, s);
    No *atual = topo;
    int pos = 1;
    while (atual!=s && atual->rotulo != n){
        atual = *baixo(b, atual);
        pos++;
    }
    // n nao encontrada
    if (atual == s){
        return 0;
    }
    // ja esta no topo
    if (atual == topo){
        return 1;
    }
    // tira a carta da posicao atual
    No *de_baixo = *baixo(b, atual);
    No *de_cima = *cima(b, atual);
    *cima(b, de_baixo) = de_cima;
    *baixo(b, de_cima) = de_baixo;
    // coloca a carta no topo
    *cima(b, atual) = s;
    *baixo(b, atual) = topo;
    *cima(b, topo) = atual;
    *baixo(b, s) = atual;
    return pos;
}

// inverte o baralho inteiro: so troca a flag, O(1)
void vira_sem_reg (Baralho *b){
    if (b == NULL){
        return;
    }
    b->invertido = !b->invertido;
}

// inverte as k cartas de cima
void vira_topo_sem_reg (Baralho *b, int k) {
    if (b == NULL || b->sentinela == NULL || k < 1)
        return;

    No *s = b->sentinela;
    No *topo = *baixo(b, s);
    No *base = topo;

    // anda ate a k-esima carta a partir do topo
    for (int i = 1; i < k && base != s; i++){
        base = *baixo(b, base);
    }

    // k maior que o baralho (ou baralho vazio)
    if (base == s){
        return;
    }

    // carta logo abaixo do trecho (pode ser a sentinela)
    No *abaixo = *baixo(b, base);

    // troca proximo e anterior dos k nos (a troca vale nos dois sentidos)
    No *p = topo;
    No *aux;
    for (int i = 0; i < k; i++) {
        aux = *baixo(b, p);
        No *t = p->anterior;
        p->anterior = p->proximo;
        p->proximo = t;
        p = aux;
    }

    // religa as pontas
    *cima(b, abaixo) = topo;
    *baixo(b, topo) = abaixo;
    *cima(b, base) = s;
    *baixo(b, s) = base;
}

// corta e registra no historico (guarda o antigo topo)
void corta (Baralho *b, int n){
    if (b == NULL || b->sentinela == NULL){
        return;
    }
    Registro r = {'C', carta(b, 1), 0};
    corta_sem_reg(b, n);
    hist_push(b->hist, r);
}

// sobe e registra no historico (guarda a posicao original da carta)
void sobe (Baralho *b, int n){
    if (b == NULL || b->sentinela == NULL){
        return;
    }
    // uma passada so: sobe_sem_reg ja devolve a posicao original
    Registro r = {'S', n, sobe_sem_reg(b, n)};
    hist_push(b->hist, r);
}

// vira e registra no historico
void vira (Baralho *b){
    if (b == NULL || b->sentinela == NULL){
        return;
    }
    Registro r = {'V', 0, 0};
    vira_sem_reg(b);
    hist_push(b->hist, r);
}

// vira_topo e registra no historico
void vira_topo (Baralho *b, int k){
    if (b == NULL || b->sentinela == NULL){
        return;
    }
    Registro r = {'T', k, 0};
    vira_topo_sem_reg(b, k);
    hist_push(b->hist, r);
}

// desfaz a operacao mais recente do historico
// usa as versoes sem_reg para o desfazer nao entrar no historico
void desfaz (Baralho *b){
    if (b == NULL){
        return;
    }
    Registro r;
    // historico vazio: nao faz nada
    if (!hist_pop(b->hist, &r)){
        return;
    }
    switch (r.tipo){
        case 'C':
            // gira de novo ate o antigo topo
            corta_sem_reg(b, r.arg);
            break;
        case 'S':
            // inverte as p primeiras e depois as p-1 primeiras
            vira_topo_sem_reg(b, r.pos);
            if (r.pos > 1){
                vira_topo_sem_reg(b, r.pos - 1);
            }
            break;
        case 'V':
            vira_sem_reg(b);
            break;
        case 'T':
            vira_topo_sem_reg(b, r.arg);
            break;
    }
}

// retorna a posicao da carta p contando a partir do topo (0 se nao achar)
int pos_carta (Baralho *b, int p){
    int contador = 1;
    if (b==NULL || b->sentinela->proximo == b->sentinela){
        return 0;
    }
    // conta a partir do topo
    No *atual = *baixo(b, b->sentinela);
    while (atual!=b->sentinela && atual->rotulo != p){
        atual = *baixo(b, atual);
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
    No *atual = *baixo(b, b->sentinela);
    while (atual != b->sentinela){
        printf("%d", atual->rotulo);
        atual = *baixo(b, atual);
        // espaco entre as cartas, quebra de linha depois da ultima
        putchar(atual == b->sentinela ? '\n' : ' ');
    }
}
//mostra o rotulo da carta na posicao p
int carta (Baralho *b, int p){
    if (b== NULL || b->sentinela->proximo == b->sentinela){
        return -1;
    }
    No *atual = *baixo(b, b->sentinela);
    int contador= 1;
    while (contador != p && atual != b->sentinela){
        atual = *baixo(b, atual);
        contador++;
    }
    if (atual == b->sentinela){
        return -1;
    }
    else {
        return atual->rotulo;
    }
}