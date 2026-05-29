#include "gameplay.h"

void moverjogador(char mapa[LINHAS][COLUNAS+1],int *andarX, int *andarY){

    if(IsKeyPressed(KEY_W) && mapa[*andarY - 1][*andarX] != '#' && mapa[*andarY - 1][*andarX] != '*'){
        (*andarY)--;
    }
    if(IsKeyPressed(KEY_S) && mapa[*andarY + 1][*andarX] != '#' && mapa[*andarY + 1][*andarX] != '*'){
        (*andarY)++;
    }
    if(IsKeyPressed(KEY_A) && mapa[*andarY][*andarX - 1] != '#' && mapa[*andarY][*andarX - 1] != '*'){
        (*andarX)--;
    }
    if(IsKeyPressed(KEY_D) && mapa[*andarY][*andarX + 1] != '#' && mapa[*andarY][*andarX + 1] != '*'){
        (*andarX)++;
    }
}


void carregarMapa(char mapa[LINHAS][COLUNAS+1],char novaFase[LINHAS][COLUNAS+1]){
    for(int y=0;y <LINHAS;y++){
        for(int x=0;x < COLUNAS + 1;x++){
            mapa[y][x] = novaFase[y][x];
        }
    }
}

void resetarJogo(char mapa[LINHAS][COLUNAS+1],bomba *bomba1,inimigo inimigos[5],int *vidas,int *fase,int *faseatual,int *andarX,int *andarY,float *tempoJogo){
    *vidas =3;

    *fase=1;
    *faseatual=1;

    *tempoJogo=0;

    *andarX=10;
    *andarY =6;

    carregarMapa(mapa, mapa);

    inimigos[0].x = 15;
    inimigos[0].y = 8;
    inimigos[0].vivo = 1;

    for(int i=1;i<5;i++){
        inimigos[i].vivo = 0;
    }

    bomba1->ativa = 0;
    bomba1->explosao = 0;
}
