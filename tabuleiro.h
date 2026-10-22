#ifndef TABULERIRO_H
#define TABULERIRO_H

typedef struct {
    int matriz[3][3];
}Tabuleiro;

void inicializarTabuleiro(Tabuleiro *t);
void desenhar(Tabuleiro *t);
int jogada(Tabuleiro *t, int linha, int coluna, int tipo);
int resultado(Tabuleiro *t);

#endif