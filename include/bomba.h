#ifndef BOMBA_H
#define BOMBA_H

#include "render.h"

void colocarbomba(bomba *bomba1,int andarX,int andarY);

void atualizarbomba(char mapa[LINHAS][COLUNAS+1],bomba *bomba1,int *andarX,int *andarY,int *vidas,inimigo inimigos[5]);

#endif