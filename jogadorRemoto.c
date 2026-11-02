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
