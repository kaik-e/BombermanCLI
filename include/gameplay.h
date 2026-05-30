#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "render.h"

void moverjogador(
    char mapa[LINHAS][COLUNAS+1],
    int *andarX,
    int *andarY
);

void carregarMapa(
    char mapa[LINHAS][COLUNAS+1],
    char novaFase[LINHAS][COLUNAS+1]
);

void resetarJogo(
    char mapa[LINHAS][COLUNAS+1],
    bomba *bomba1,
    inimigo inimigos[5],
    int *vidas,
    int *fase,
    int *faseatual,
    int *andarX,
    int *andarY,
    float *tempoJogo
);

#endif