#include <stdio.h>
#include "partida.h"
#include "tabuleiro.h"
#include "jogadorTeclado.h"

void iniciarPartida(void){
    Tabuleiro tabuleiro;
    JogadorTeclado jogador1 = {1};
    JogadorTeclado jogador2 = {2};
    JogadorTeclado *atual = &jogador1;

    int linha, coluna;
    int estado = 0;
    inicializarTabuleiro(&tabuleiro);
    while(estado == 0){
        desenhar(&tabuleiro);
        jogar(atual, &linha, &coluna);
        if(jogada(&tabuleiro, linha, coluna, atual->tipo) == 0){
            continue;
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
    if(estado == 1){
        printf("Jogador X venceu!\n");
    } else if (estado == 2){
        printf("Jogador O venceu!\n");
    } else {
        printf("Empate!\n");
    }
}