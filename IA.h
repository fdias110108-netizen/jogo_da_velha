#ifndef IA_H
#define IA_H

#include "tabuleiro.h"

int R1(Tabuleiro *t, int alvo, int tipoIA, int possibilidades[8][3]);
int R2(Tabuleiro *t, int tipoIA, int possibilidades[8][3]);
int R3(Tabuleiro *t, int tipoIA);
int R4(Tabuleiro *t, int tipoIA, int cantos[4][2]);
int R5(Tabuleiro *t, int tipoIA, int cantos[4][2]);
int R6(Tabuleiro *t, int tipoIA);
int jogarIA(Tabuleiro *t, int tipoIA);
#endif