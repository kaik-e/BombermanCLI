#ifndef INIMIGO_H
#define INIMIGO_H

#include "render.h"

void moverinimigo(
    char mapa[LINHAS][COLUNAS+1],
    inimigo *inimigo1,
    int *andarX,
    int *andarY,
    int *vidas
);

#endif