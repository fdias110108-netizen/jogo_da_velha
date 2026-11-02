
#ifndef JOGADOR_REMOTO_H
#define JOGADOR_REMOTO_H

#include <winsock2.h>
#include "tabuleiro.h"

typedef struct {
    int tipo;
    SOCKET sock;
} JogadorRemoto;

int iniciarSocket(void);
int conectar(JogadorRemoto *j, const char *ip, int porta);
int aceitar(JogadorRemoto *j, int porta);
int enviaJogada(JogadorRemoto *j, int linha, int coluna);
int jogarRemoto(JogadorRemoto *j, Tabuleiro *tabuleiro);
void desconectar(JogadorRemoto *j);
void finalizarSocket(void);

#endif
