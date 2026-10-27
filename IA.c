#include <stdio.h>
#include "IA.h"

int R1(Tabuleiro *t, int alvo, int tipoIA, int possibilidades[8][3]){
    for(int i = 0; i<8; i++){
        int quantidade = 0;
        int posicaoLivre = -1;
        for(int j = 0; j<3; j++){
            int linha = possibilidades[i][j]/3;
            int coluna = possibilidades[i][j] % 3;
            if(t->matriz[linha][coluna] == alvo){
                quantidade++;
            }
            if(t->matriz[linha][coluna] == 0){
                posicaoLivre = possibilidades[i][j];
            }
        }
        if(quantidade == 2 && posicaoLivre != -1){
            int linha = posicaoLivre/3;
            int coluna = posicaoLivre %3;
            return jogada(t, linha+1, coluna+1, tipoIA);
        }
    }
    return 0;
}
int R2(Tabuleiro *t, int tipoIA, int possibilidades[8][3]){
    for(int i = 0; i<3;i++){
        for(int j = 0; j<3;j++){
            if(t->matriz[i][j]!=0){
                continue;
            }
            t->matriz[i][j] = tipoIA;
            int sequencias = 0;
            for(int k = 0;k<8;k++){
                int quantidade = 0;
                int vazias = 0;
                for(int p = 0; p<3; p++){
                    int linha = possibilidades[k][p]/3;
                    int coluna = possibilidades[k][p]%3;
                    if(t->matriz[linha][coluna] == tipoIA){
                        quantidade++;
                    }
                    if(t->matriz[linha][coluna] == 0){
                        vazias++;
                    }
                }
                if(quantidade == 2 && vazias == 1){
                    sequencias++;
                }
            }
            t->matriz[i][j] = 0;
            if(sequencias >= 2){
                return jogada(t, i+1, j+1, tipoIA);
            }
        }
    }
    return 0;
}
int R3(Tabuleiro *t, int tipoIA){
    if(t->matriz[1][1] == 0){
        return jogada(t, 2, 2, tipoIA);
    }
    return 0;
}
int R4(Tabuleiro *t, int tipoIA, int cantos[4][2]){
    for(int i = 0; i<4; i++){
        int linhaA = cantos[i][0]/3;
        int colunaA = cantos[i][0]%3;

        int linhaIA = cantos[i][1]/3;
        int colunaIA = cantos[i][1]%3;

        if(t->matriz[linhaA][colunaA] == 4 && t->matriz[linhaIA][colunaIA] == 0){
            return jogada(t, linhaIA + 1, colunaIA + 1, tipoIA);
        }
    }
    return 0;
}
int R5(Tabuleiro *t, int tipoIA, int cantos[4][2]){
    for(int i = 0; i<4; i++){
        int linha = cantos[i][0]/3;
        int coluna = cantos[i][0]%3;
        if(t->matriz[linha][coluna] == 0){
            return jogada(t, linha+1, coluna+1, tipoIA);
        }
    }
    return 0;
}
int R6(Tabuleiro *t, int tipoIA){
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            if(t->matriz[i][j] == 0){
                return jogada(t, i+1, j+1, tipoIA);
            }
        }
    }
    return 0;
}
int jogarIA(Tabuleiro *t, int tipoIA){
    int possibilidades[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6},
    };
    int cantos[4][2] = {
        {0, 8},
        {2, 6},
        {6, 2},
        {8, 0},
    };
    if(R1(t, tipoIA, tipoIA, possibilidades)){
        return 1;
    }
    if(R1(t, 4, tipoIA, possibilidades)){
        return 1;
    }
    if(R2(t, tipoIA, possibilidades)){
        printf("Executou R2.\n");
        return 1;
    }
    if(R3(t, tipoIA)){
        return 1;
    }
    if(R4(t, tipoIA, cantos)){
        return 1;
    }
    if(R5(t, tipoIA, cantos)){
        return 1;
    }
    if(R6(t, tipoIA)){
        return 1;
    }
    return 0;
}