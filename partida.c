
#include <stdio.h>
#include "partida.h"
#include "tabuleiro.h"
#include "jogadorTeclado.h"
#include "jogadorRemoto.h"
#include "IA.h"

#define PORTA 8080

void iniciarPartida(int modoJogo) {
    Partida partida;
    JogadorRemoto remoto;

    int linha, coluna;
    int erroRede = 0;
    int usaRede = (modoJogo == 3 || modoJogo == 4);
    remoto.sock = INVALID_SOCKET;
    inicializarTabuleiro(&partida.tabuleiro);
    partida.jogadores[0].tipo = 4;
    partida.jogadores[1].tipo = 1;
    partida.atual = 0;
    partida.estado = 0;
    partida.modoJogo = modoJogo;
    switch (modoJogo) {
        case 1:
            partida.jogadores[0].controle = TECLADO;
            partida.jogadores[1].controle = TECLADO;
            break;
        case 2:
            partida.jogadores[0].controle = TECLADO;
            partida.jogadores[1].controle = COMPUTADOR;
            break;
        case 3:
            partida.jogadores[0].controle = TECLADO;
            partida.jogadores[1].controle = REMOTO;
            break;
        case 4:
            partida.jogadores[0].controle = REMOTO;
            partida.jogadores[1].controle = TECLADO;
            break;
        default:
            printf("Modo invalido!\n");
            return;
    }
    if (usaRede) {
        if (!iniciarSocket()) {
            return;
        }
        int conectado = 0;
        if (modoJogo == 3) {
            remoto.tipo = 1;
            conectado = aceitar(&remoto, PORTA);
        }
        else {
            char ip[64];
            remoto.tipo = 4;
            printf("Digite o IP do servidor: ");

            if (scanf("%63s", ip) == 1) {
                conectado = conectar(&remoto, ip, PORTA);
            }
        }
        if (!conectado) {
            desconectar(&remoto);
            finalizarSocket();
            return;
        }
    }
    while (partida.estado == 0) {
        desenhar(&partida.tabuleiro);
        Jogador *atual =
            &partida.jogadores[partida.atual];

        if (atual->controle == COMPUTADOR) {
            printf("Vez da IA!\n");
            jogarIA(&partida.tabuleiro, atual->tipo);
        }
        else if (atual->controle == REMOTO) {
            if (!jogarRemoto(&remoto, &partida.tabuleiro)) {
                erroRede = 1;
                break;
            }
        }
        else if (atual->controle == TECLADO) {
            JogadorTeclado teclado = {atual->tipo};
            jogar(&teclado, &linha, &coluna);
            if (jogada(&partida.tabuleiro,
                       linha, coluna, atual->tipo) == 0) {
                continue;
            }
            if (usaRede) {
                if (!enviaJogada(&remoto, linha, coluna)) {
                    printf("Erro ao enviar jogada!\n");
                    erroRede = 1;
                    break;
                }
            }
        }
        partida.estado = resultado(&partida.tabuleiro);
        if (partida.estado == 0) {
            partida.atual = 1 - partida.atual;
        }
    }
    desenhar(&partida.tabuleiro);
    if (erroRede) {
        printf("Partida interrompida por erro de rede.\n");
    }
    else if (partida.estado == 4) {
        printf("Jogador X venceu!\n");
    }
    else if (partida.estado == 1) {
        if (modoJogo == 2) {
            printf("A IA venceu!\n");
        }
        else {
            printf("Jogador O venceu!\n");
        }
    }
    else if (partida.estado == 3) {
        printf("Empate!\n");
    }
    if (usaRede) {
        desconectar(&remoto);
        finalizarSocket();
    }
}