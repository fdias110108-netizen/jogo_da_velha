#ifndef PARTIDA_H
#define PARTIDA_H

#include "tabuleiro.h"
#include "jogadorTeclado.h"

typedef enum {
    TECLADO = 1,
    COMPUTADOR = 2,
    REMOTO = 3,
}TipoControle;

typedef struct {
    int tipo;
    TipoControle controle;
}Jogador;

typedef struct {
    Tabuleiro tabuleiro;
    Jogador jogadores[2];
    int atual;
    int modoJogo;
    int estado;
} Partida;

void iniciarPartida(int modoJogo);

#endif