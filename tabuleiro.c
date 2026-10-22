#include <stdio.h>
#include "tabuleiro.h"

void inicializarTabuleiro(Tabuleiro *t){
    for(int i = 0; i<3;i++){
        for(int j = 0; j<3; j++){
            t->matriz[i][j] = 0;
        }
    }
}
void desenhar(Tabuleiro *t){
    for(int i = 0; i<3; i++){
        for(int j = 0; j < 3; j++){
            if(t->matriz[i][j] == 0){
                printf("   ");
            } else if (t->matriz[i][j] == 1){
                printf(" X ");
            } else {
                printf(" O ");
            }
            if(j < 2){
                printf("|");
            }
        }
        printf("\n");
        if(i < 2){
            printf("___|___|___\n");
        }
    }
}
int jogada(Tabuleiro *t, int linha , int coluna , int tipo){
    if(linha < 1|| linha > 3|| coluna <1 || coluna>3){
        printf("Posicao invalida!\n");
        return 0;
    }
    linha --;
    coluna--;
    if(t->matriz[linha][coluna] != 0){
        printf("Posicao ocupada!\n");
        return 0;
    }
    t->matriz[linha][coluna] = tipo;
    return 1;
}
int resultado(Tabuleiro *t){
    for(int i = 0; i< 3; i++){
        if(t->matriz[i][0] != 0 && t->matriz[i][0] == t->matriz[i][1] && t->matriz[i][1] == t-> matriz[i][2]){
            return t->matriz[i][0];
        }
    }
    for(int j = 0; j < 3; j++){
        if(t->matriz[0][j] != 0 && t->matriz[0][j] == t->matriz[1][j] && t->matriz[1][j] == t->matriz[2][j]){
            return t->matriz[0][j];
        }
    }
    if(t->matriz[0][0] != 0 && t->matriz[0][0] == t->matriz[1][1] && t->matriz[1][1] == t->matriz[2][2]){
        return t->matriz[0][0];
    }
    if(t->matriz[0][2] != 0 && t->matriz[0][2] == t->matriz[1][1] && t->matriz[1][1] == t->matriz[2][0]){
        return t->matriz[0][2];
    }
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            if(t->matriz[i][j] == 0){
                return 0;
            }
        }
    }
    return 3;
}