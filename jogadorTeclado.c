#include <stdio.h>
#include "jogadorTeclado.h"

void jogar(JogadorTeclado *j, int *linha, int *coluna){
    if(j->tipo == 1){
        printf("Jogador X\n");
    } else {
        printf("Jogador O\n");
    }
    printf("Digite a linha (1 a 3): ");
    scanf("%d", linha);

    printf("Digite a coluna (1 a 3): ");
    scanf("%d", coluna);
}