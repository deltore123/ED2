/* gerador.c: so imprime, na saida padrao, uma sequencia de comandos.
   Nao conhece nenhum baralho.

   uso: ./gerador RAJADA n [semente]
     RAJADA: SOBE, CARTA, POSICAO, CORTA ou DESFAZ
     n:      numero de cartas do baralho
     semente (opcional): a mesma semente gera sempre a mesma entrada

   saida: BARALHO n, depois m = 2n comandos da rajada e, por fim, FIM.
   Os sorteios sao uniformes: cada x ou p sai de 1 a n. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long long estado;

/* xorshift64: da o mesmo resultado em qualquer sistema
   (o rand() do Windows so chega a 32767, pouco para n = 100000) */
static unsigned long long proximo(void){
    estado ^= estado << 13;
    estado ^= estado >> 7;
    estado ^= estado << 17;
    return estado;
}

/* sorteio uniforme entre 1 e n */
static long sorteia(long n){
    return 1 + (long)(proximo() % (unsigned long long)n);
}

/* uma operacao sorteada entre CORTA x, VIRA e SOBE x */
static void operacao_sorteada(long n){
    long tipo = sorteia(3);
    if (tipo == 1){
        printf("CORTA %ld\n", sorteia(n));
    } else if (tipo == 2){
        printf("VIRA\n");
    } else {
        printf("SOBE %ld\n", sorteia(n));
    }
}

int main(int argc, char *argv[]){
    if (argc < 3 || argc > 4){
        fprintf(stderr, "uso: %s RAJADA n [semente]\n", argv[0]);
        fprintf(stderr, "RAJADA: SOBE, CARTA, POSICAO, CORTA ou DESFAZ\n");
        return 1;
    }

    char *rajada = argv[1];
    if (strcmp(rajada, "SOBE") != 0 && strcmp(rajada, "CARTA") != 0 &&
        strcmp(rajada, "POSICAO") != 0 && strcmp(rajada, "CORTA") != 0 &&
        strcmp(rajada, "DESFAZ") != 0){
        fprintf(stderr, "rajada desconhecida: %s\n", rajada);
        return 1;
    }

    char *fim;
    long n = strtol(argv[2], &fim, 10);
    if (*fim != '\0' || n < 1){
        fprintf(stderr, "n invalido: %s\n", argv[2]);
        return 1;
    }

    unsigned long long semente = 1;
    if (argc == 4){
        semente = strtoull(argv[3], &fim, 10);
        if (*fim != '\0'){
            fprintf(stderr, "semente invalida: %s\n", argv[3]);
            return 1;
        }
    }
    estado = semente * 0x9E3779B97F4A7C15ULL + 0x2545F4914F6CDD1DULL;
    if (estado == 0){
        estado = 1;
    }
    for (int i = 0; i < 10; i++){   /* aquece o gerador */
        proximo();
    }

    long m = 2 * n;
    printf("BARALHO %ld\n", n);

    for (long i = 0; i < m; i++){
        if (strcmp(rajada, "SOBE") == 0){
            printf("SOBE %ld\n", sorteia(n));
        } else if (strcmp(rajada, "CARTA") == 0){
            printf("CARTA %ld\n", sorteia(n));
        } else if (strcmp(rajada, "POSICAO") == 0){
            printf("POSICAO %ld\n", sorteia(n));
        } else if (strcmp(rajada, "CORTA") == 0){
            /* CORTA x ou VIRA, com a mesma chance */
            if (sorteia(2) == 1){
                printf("CORTA %ld\n", sorteia(n));
            } else {
                printf("VIRA\n");
            }
        } else {
            /* trincas: duas operacoes sorteadas e um DESFAZ
               (como m nem sempre e multiplo de 3, a ultima pode ficar incompleta).
               o enunciado e ambiguo aqui: confirmar com os estagiarios. */
            if (i % 3 == 2){
                printf("DESFAZ\n");
            } else {
                operacao_sorteada(n);
            }
        }
    }

    printf("FIM\n");
    return 0;
}
