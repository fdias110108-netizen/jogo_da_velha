#include <stdio.h>
#include "partida.h"
#include "tabuleiro.h"
#include "jogadorTeclado.h"
#include "IA.h"

void iniciarPartida(int modoJogo){
    Partida partida;
    partida.jogadores[0].tipo = 4;
    partida.jogadores[1].tipo = 1;
    partida.atual = 0;
    partida.modoJogo = modoJogo;
    partida.estado = 0;

    int linha, coluna;
    inicializarTabuleiro(&partida.tabuleiro);
    while(partida.estado == 0){
        desenhar(&partida.tabuleiro);
        JogadorTeclado *atual = &partida.jogadores[partida.atual];
        if(partida.modoJogo == 2 && partida.atual == 1){
            printf("Vez da IA!\n");
            jogarIA(&partida.tabuleiro, atual->tipo);
        }
        else{
            jogar(atual, &linha, &coluna);
            if(jogada(&partida.tabuleiro, linha, coluna, atual->tipo) == 0){
                continue;
            }
        }
        partida.estado = resultado(&partida.tabuleiro);
        if(partida.estado == 0){
            partida.atual = 1 - partida.atual;
        }
    }
    desenhar(&partida.tabuleiro);
    if(partida.estado == 4){
        printf("Jogador X venceu!\n");
    } else if (partida.estado == 1){
        if(partida.modoJogo == 2){
            printf("A IA venceu!\n");
        }
        else{
            printf("Jogador O venceu!\n");
        }
    } else if(partida.estado == 3){
        printf("Empate!\n");
    }
}