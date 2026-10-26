#ifndef IA_H
#define IA_H

#include "tabuleiro.h"

typedef struct{
    int tipo;
} JogadorIA;

void jogarIA(JogadorIA *ia, Tabuleiro *t);
int R1(Tabuleiro *t, int alvo, int tipoIA);
#endif