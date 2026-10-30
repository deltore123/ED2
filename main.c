// Importando as bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Importando assinaturas do tad.h
#include "tad.h"

int main(void){
    Baralho* baralho = NULL;

    while(1){
        // Escaneia Comando para comparar no loop
        char comando[15];
        if (scanf("%14s", comando) != 1) {
            break;
        }
        
        // Se comando digitado for x faz lógica qude chama a função

        // Função que cria baralho
        if (strcmp(comando, "BARALHO") == 0){
            // Lê número de  cartas do baralho 
            int n;
            if (scanf("%d", &n) != 1) {
                break;
            }
            
            // Chama função para cirar o baralho 
            if (baralho != NULL) {
                limpa(baralho);
            }

            baralho = criar(n);
        }

        // Corta baralho acima da carta x ( cartas vão para o fundo na mesma ordem)
        else if (strcmp(comando, "CORTA") == 0){
            // Lê x 
            int x;
            if (scanf("%d", &x) != 1) {
                break;
            }

            corta(baralho, x);
        }

        // Tira x de onde estiver e coloca no topo
        else if (strcmp(comando, "SOBE") == 0){
            // Lê x 
            int x;
            if (scanf("%d", &x) != 1) {
                break;
            }

            sobe(baralho, x);
        }

        // Inverte baralho ( carta do funo vai para o topo)
        else if (strcmp(comando, "VIRA") == 0){
            vira(baralho);
        }

        // Inverte só as k cartas de cima
        else if (strcmp(comando, "VIRATOPO") == 0){
            // Lê k
            int k;
            if (scanf("%d", &k) != 1) {
                break;
            }

            vira_topo(baralho, k);
        }

        // Retorna o rótulo da carta de posição p 
        else if (strcmp(comando, "CARTA") == 0){
            int p;
            if (scanf("%d", &p) != 1) {
                break;
            }
            printf("%d\n", carta(baralho, p));
        }

        // Retorna a posição da carta x 
        else if (strcmp(comando, "POSICAO") == 0){
            //Lê X
            int x;
            if (scanf("%d", &x) != 1) {
                break;
            }
            printf("%d\n", pos_carta(baralho, x));
        }
        
        // Desfaz a operação mais recente do histórico
        else if (strcmp(comando, "DESFAZ") == 0){
            desfaz(baralho);
        }

        // Mostra os rótulos do baralho do topo ao fundo
        else if (strcmp(comando, "MOSTRA") == 0){
            mostra(baralho);
        }

        // Encerra ciclo
        else if (strcmp(comando, "FIM") == 0){
            break;
        }
    }

    limpa(baralho);

    return 0;
}
