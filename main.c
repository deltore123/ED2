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
            scanf("%d", &n);
            
            // Chama função para cirar o baralho 
            if (baralho != NULL) {
                limpa(baralho);
            }

            baralho = criar(n);
            if (baralho == NULL) {
                printf("Erro na execução do comando\n");
            }
        }

        // Corta baralho acima da carta x ( cartas vão para o fundo na mesma ordem)
        else if (strcmp(comando, "CORTA") == 0){
            // Lê x 
            int x;
            scanf("%d", &x);

            // Chama função 
            int verificacao = corta(baralho, x);

            // Verifica se deu errado
            if (verificacao == 0){
                printf("Erro na execução do comando\n");
            }

        }

        // Tira x de onde estiver e coloca no topo
        else if (strcmp(comando, "SOBE") == 0){
            // Lê x 
            int x;
            scanf("%d", &x);

            // Chama função
            int verificacao = sobe(baralho, x);

             // Verifica se deu errado
            if (verificacao == 0){
                printf("Erro na execução do comando\n");
            }
        }

        // Inverte baralho ( carta do funo vai para o topo)
        else if (strcmp(comando, "VIRA") == 0){
             // Chama função
            int verificacao = vira(baralho);

             // Verifica se deu errado
            if (verificacao == 0){
                printf("Erro na execução do comando\n");
            }
        }

        // Inverte só as k cartas de cima
        else if (strcmp(comando, "VIRATOPO") == 0){
            // Lê k
            int k;
            scanf("%d", &k);

            // Chama função
            int verificacao = vira_topo(baralho,k);

            // Verifica se deu errado
            if (verificacao == 0){
                printf("Erro na execução do comando\n");
            }
        }

        // Retorna o rótulo da carta de posição p 
        else if (strcmp(comando, "CARTA") == 0){
            int p;
            scanf("%d", &p);
            int rotulo = carta(baralho, p);
            if (rotulo == -1) {
                printf("Erro na execução do comando\n");
            } else {
                printf("%d\n", rotulo);
            }
        }

        // Retorna a posição da carta x 
        else if (strcmp(comando, "POSICAO") == 0){
            //Lê X
            int x;
            scanf("%d", &x);
            // Chama função
            int verificacao = pos_carta(baralho,x);

            // Verifica se deu errado
            if (verificacao == 0){
                printf("Erro na execução do comando\n");
            } else {
                printf("%d\n", verificacao);
            }
        }
        
        // Mostra os rótulos do baralho do topo ao fundo
        else if (strcmp(comando, "MOSTRA") == 0){
            // Chama função
            mostra(baralho);
        }

        // Encerra ciclo
        else if (strcmp(comando, "FIM") == 0){
            break;
        }
        else {
            printf("Erro na execução do comando\n");
        }
    }

    limpa(baralho);

    return 0;
}

