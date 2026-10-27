#include <stdio.h>
#include "partida.h"

int main(){
    int modoJogo = 0;
    while(modoJogo != 1 && modoJogo != 2){
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
    }
    return 0;
}