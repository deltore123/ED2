// Importando as bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Importando assinaturas do tad.h
#include "tad.h"

int main(void){
    while(1){
        // Declara variavel que será usada com baralho
        Baralho* baralho = NULL; 
        // Escaneia Comando para comparar no loop
        char comando[15];
        scanf("%s ", comando);
        
        // Se comando digitado for x faz lógica qude chama a função

        // Função que cria baralho
        if( strcmp(comando, "BARALHO") == 1){
            // Lê número de  cartas do baralho 
            int n;
            scanf("%d", &n);
            
            // Chama função para cirar o baralho 

            baralho = criar(n);
        }

        // Corta baralho acima da carta x ( cartas vão para o fundo na mesma ordem)
        if( strcmp(comando, "CORTA") == 1){
            // Lê x 
            int x;
            scanf("%d", &x);

            // Chama função 
            int verificação = corta(baralho);

            // Verifica se deu errado
            if ( verificação == 0){
                printf("Erro na execução do comando");
            }

        }

        // Tira x de onde estiver e coloca no topo
        if( strcmp(comando, "SOBE") == 1){
            // Lê x 
            int x;
            scanf("%d", &x);

            // Chama função
            int verificação = sobre(baralho);

             // Verifica se deu errado
            if ( verificação == 0){
                printf("Erro na execução do comando");
            }
        }

        // Inverte baralho ( carta do funo vai para o topo)
        if( strcmp(comando, "VIRA") == 1){
             // Chama função
            int verificação = vira(baralho);

             // Verifica se deu errado
            if ( verificação == 0){
                printf("Erro na execução do comando");
            }
        }

        // Inverte só as k cartas de cima
        if( strcmp(comando, "VIRATOPO") == 1){
            // Lê k
            int k;
            scanf("%d", &k);

            // Chama função
            int verificação = vira_topo(baralho,k);

            // Verifica se deu errado
            if ( verificação == 0){
                printf("Erro na execução do comando");
            }
        }

        // Desfaz operação mais recente no histórico da main
        if( strcmp(comando, "DESFAZ") == 1){
            // Chama função
            int verificação = desfaz(baralho);

            // Verifica se deu errado
            if ( verificação == 0){
                printf("Erro na execução do comando");
            }
        }

        // Retorna o rótulo da carta de posição p 
        if( strcmp(comando, "CARTA") == 1){
            
        }

        // Retorna a posição da carta x 
        if( strcmp(comando, "POSICAO") == 1){
            //Lê X
            int x;
            scanf("%d", &x);
            // Chama função
            int verificação = pos_carta(baralho,x);

            // Verifica se deu errado
            if ( verificação == 0){
                printf("Erro na execução do comando");
            }
        }
        
        // Mostra os rótulos do baralho do topo ao fundo
        if( strcmp(comando, "MOSTRA") == 1){
            // Chama função
            mostra(baralho);
        }

        // Encerra ciclo
        if( strcmp(comando, "FIM") == 1){
            break;
        }
    }

    return 0;
}

