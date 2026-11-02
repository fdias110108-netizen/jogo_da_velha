#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "jogadorRemoto.h"

int iniciarSocket(void){
    WSADATA dados;
    if (WSAStartup(MAKEWORD(2, 2), &dados) != 0){
        printf("Erro ao iniciar Winsock!\n");
        return 0;
    }
    return 1;
}
int conectar(JogadorRemoto *j, const char *ip, int porta){
    struct sockaddr_in servidor = {0};
    j->sock = INVALID_SOCKET;
    j->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(j->sock == INVALID_SOCKET){
        printf("Erro ao criar socket!\n");
        return 0;
    }
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons((unsigned short)porta);
    unsigned long endereco = inet_addr(ip);
    if (endereco == INADDR_NONE) {
        printf("Endereco IP invalido!\n");
        desconectar(j);
        return 0;
    }
    servidor.sin_addr.s_addr = endereco;
    if (connect(j->sock,(struct sockaddr *)&servidor, sizeof(servidor)) == SOCKET_ERROR) {
        printf("Erro ao conectar: %d\n", WSAGetLastError());
        desconectar(j);
        return 0;
    }
    printf("Conectado ao servidor!\n");
    return 1;
}
int aceitar(JogadorRemoto *j, int porta) {
    SOCKET servidor_fd;
    struct sockaddr_in endereco = {0};

    j->sock = INVALID_SOCKET;

    servidor_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (servidor_fd == INVALID_SOCKET) {
        printf("Erro ao criar socket!\n");
        return 0;
    }

    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = htonl(INADDR_ANY);
    endereco.sin_port = htons((unsigned short)porta);

    if (bind(servidor_fd,
             (struct sockaddr *)&endereco,
             sizeof(endereco)) == SOCKET_ERROR) {
        printf("Erro no bind: %d\n", WSAGetLastError());
        closesocket(servidor_fd);
        return 0;
    }

    if (listen(servidor_fd, 1) == SOCKET_ERROR) {
        printf("Erro no listen!\n");
        closesocket(servidor_fd);
        return 0;
    }

    printf("Aguardando jogador na porta %d...\n", porta);

    j->sock = accept(servidor_fd, NULL, NULL);

    closesocket(servidor_fd);

    if (j->sock == INVALID_SOCKET) {
        printf("Erro ao aceitar conexao!\n");
        return 0;
    }

    printf("Jogador conectado!\n");
    return 1;
}
static int enviarTudo(SOCKET sock, const char *dados, int tamanho) {
    int total = 0;

    while (total < tamanho) {
        int bytes = send(sock, dados + total, tamanho - total, 0);

        if (bytes == SOCKET_ERROR || bytes == 0) {
            return 0;
        }

        total += bytes;
    }

    return 1;
}
static int receberTudo(SOCKET sock, char *dados, int tamanho) {
    int total = 0;

    while (total < tamanho) {
        int bytes = recv(sock, dados + total, tamanho - total, 0);

        if (bytes == SOCKET_ERROR || bytes == 0) {
            return 0;
        }

        total += bytes;
    }

    return 1;
}
int enviaJogada(JogadorRemoto *j, int linha, int coluna) {
    unsigned char dados[2];

    if (linha < 0 || linha > 2 ||
        coluna < 0 || coluna > 2) {
        return 0;
    }

    dados[0] = (unsigned char)linha;
    dados[1] = (unsigned char)coluna;

    return enviarTudo(j->sock, (const char *)dados, 2);
}
int jogarRemoto(JogadorRemoto *j, Tabuleiro *t) {
    unsigned char dados[2];

    printf("Aguardando jogada do adversario...\n");

    if (!receberTudo(j->sock, (char *)dados, 2)) {
        printf("Adversario desconectou ou houve erro de rede!\n");
        return 0;
    }

    int linha = dados[0];
    int coluna = dados[1];

    if (linha > 2 || coluna > 2) {
        printf("Coordenadas remotas invalidas!\n");
        return 0;
    }

    if (jogada(t, linha, coluna, j->tipo) == 0) {
        printf("Jogada remota invalida!\n");
        return 0;
    }

    printf("Adversario jogou na linha %d, coluna %d\n",
           linha, coluna);

    return 1;
}
void desconectar(JogadorRemoto *j) {
    if (j->sock != INVALID_SOCKET) {
        closesocket(j->sock);
        j->sock = INVALID_SOCKET;
    }
}
void finalizarSocket(void) {
    WSACleanup();
}