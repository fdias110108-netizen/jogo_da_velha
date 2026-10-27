#include <stdio.h>
#include "partida.h"
#include "tabuleiro.h"
#include "jogadorTeclado.h"
#include "IA.h"

void iniciarPartida(int modoJogo){
    Tabuleiro tabuleiro;
    JogadorTeclado jogador1 = {4};
    JogadorTeclado jogador2 = {1};
    JogadorTeclado *atual = &jogador1;

    int linha, coluna;
    int estado = 0;
    inicializarTabuleiro(&tabuleiro);
    while(estado == 0){
        desenhar(&tabuleiro);
        if(modoJogo == 2 && atual == &jogador2){
            printf("Vez da IA!\n");
            jogarIA(&tabuleiro, jogador2.tipo);
        }
        else{
            jogar(atual, &linha, &coluna);
            if(jogada(&tabuleiro, linha, coluna, atual->tipo) == 0){
                continue;
            }
        }
        estado = resultado(&tabuleiro);
        if(estado == 0){
            if(atual == &jogador1){
                atual = &jogador2;
            } else {
                atual = &jogador1;
            }
        }
    }
    desenhar(&tabuleiro);
    if(estado == 4){
        printf("Jogador X venceu!\n");
    } else if (estado == 1){
        if(modoJogo == 2){
            printf("A IA venceu!\n");
        }
        else{
            printf("Jogador O venceu!\n");
        }
    } else {
        printf("Empate!\n");
    }
}