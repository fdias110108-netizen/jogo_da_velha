#include <stdio.h>
#include "partida.h"

int main(){
    int modoJogo = 0;
    int opcao = 0;
    do{
        printf("______JOGO DA VELHA______\n");
        printf("1- Jogador vs Jogador\n");
        printf("2 - Jogador vs IA\n");
        printf("Digite uma opcao: ");
        scanf("%d", &modoJogo);
        if(modoJogo == 1 || modoJogo == 2){
            iniciarPartida(modoJogo);
        } else {
            printf("Opcao invalida, tente novamente.");
        }
        printf("Deseja jogar novamente?\n");
        printf("1- Sim\n");
        printf("2- Nao\n");
    }while(opcao == 1);
    printf("Obrigado por jogar.");
    return 0;
}