#ifndef PARTIDA_H
#define PARTIDA_H

#include "tabuleiro.h"
#include "jogadorTeclado.h"

typedef struct {
    Tabuleiro tabuleiro;
    JogadorTeclado jogadores[2];
    int atual;
    int modoJogo;
    int estado;
} Partida;

void iniciarPartida(int modoJogo);

#endif