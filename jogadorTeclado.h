#ifndef JOGADORTECLADO_H
#define JOGADORTECLADO_H

typedef struct {
    int tipo;
} JogadorTeclado;

void jogar(JogadorTeclado *j, int *linha, int *coluna);
#endif