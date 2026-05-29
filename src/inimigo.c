#include "inimigo.h"
#include <stdlib.h>


void moverinimigo(char mapa[LINHAS][COLUNAS+1],inimigo *inimigo1, int *andarX, int *andarY, int *vidas){

    if(inimigo1->vivo == 0){
        return;
    }

    if(inimigo1->x == *andarX && inimigo1->y == *andarY){
        (*vidas)--;
        *andarX = 10;
        *andarY = 6;
    }

    inimigo1->tempoInimigo += GetFrameTime();

    if(inimigo1->tempoInimigo >= 0.7f){
        int mexeu = 0;

        if(*andarX>inimigo1->x && mapa[inimigo1->y][inimigo1->x+1] != '#' && mapa[inimigo1->y][inimigo1->x + 1] != '*'){
            inimigo1->x++;
            mexeu=1;
        }

        else if(*andarX < inimigo1->x && mapa[inimigo1->y][inimigo1->x-1] != '#' && mapa[inimigo1->y][inimigo1->x-1] != '*'){
            inimigo1->x--;
            mexeu=1;
        }

        else if(*andarY > inimigo1->y && mapa[inimigo1->y+ 1][inimigo1->x] != '#' && mapa[inimigo1->y+1][inimigo1->x] != '*'){
            inimigo1->y++;
            mexeu=1;
        }

        else if(*andarY < inimigo1->y && mapa[inimigo1->y-1][inimigo1->x] != '#' && mapa[inimigo1->y -1][inimigo1->x] != '*'){
            inimigo1->y--;
            mexeu=1;
        }

        if(mexeu==0){
            int direcao = rand() %4;

            if(direcao == 0 && mapa[inimigo1->y-1][inimigo1->x] != '#' && mapa[inimigo1->y-1][inimigo1->x] != '*'){
                inimigo1->y--;
            }

            if(direcao == 1 && mapa[inimigo1->y+1][inimigo1->x] != '#' && mapa[inimigo1->y+1][inimigo1->x] != '*'){
                inimigo1->y++;
            }

            if(direcao == 2 && mapa[inimigo1->y][inimigo1->x-1] != '#' && mapa[inimigo1->y][inimigo1->x-1] != '*'){
                inimigo1->x--;
            }

            if(direcao == 3 && mapa[inimigo1->y][inimigo1->x+1] != '#' && mapa[inimigo1->y][inimigo1->x+1] != '*'){
                inimigo1->x++;
            }
        }

        if(inimigo1->x == *andarX && inimigo1->y ==*andarY){
            (*vidas)--;
            *andarX = 10;
            *andarY = 6;
        }

        inimigo1->tempoInimigo = 0;
    }
}