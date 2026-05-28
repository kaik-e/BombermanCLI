#ifndef BOMBA_H
#define BOMBA_H

#include "render.h"

void colocarbomba(bomba* bomba1, int andarX,int andarY){
    if(IsKeyPressed(KEY_SPACE) && bomba1->ativa == 0){

        bomba1->x = andarX;
        bomba1->y = andarY;

        bomba1->ativa = 1;

        bomba1->timer = 4.0f;

        bomba1->frameBomba = 0;
        bomba1->tempoBomba = 0;
    }
}

void atualizarbomba(char mapa[LINHAS][COLUNAS+1],bomba *bomba1,int *andarX,int *andarY,int *vidas,inimigo inimigos[5]){
    if (bomba1->ativa == 1){
        bomba1->tempoBomba += GetFrameTime();

        if(bomba1->tempoBomba >= 0.8f){

            if(bomba1->frameBomba < 2){
                bomba1->frameBomba++;
            }

            bomba1->tempoBomba = 0;
        }

        bomba1->timer -= GetFrameTime();
            
        if (bomba1->timer <= 0){

            bomba1->ativa = 0;
            bomba1->explosao = 1;
            bomba1->tempoExplosao = 0.5f;

            bomba1->frameExplosao = 0;
            bomba1->tempoFrame = 0;

            // quebrar bloco
            if(mapa[bomba1->y-1][bomba1->x] == '*'){
                mapa[bomba1->y-1][bomba1->x] =' ';
            }

            if(mapa[bomba1->y+1][bomba1->x] == '*'){
                mapa[bomba1->y+1][bomba1->x] = ' ';
            }

            if(mapa[bomba1->y][bomba1->x-1] == '*'){
                mapa[bomba1->y][bomba1->x-1] =' ';
            }

            if(mapa[bomba1->y][bomba1->x+1] == '*'){
                mapa[bomba1->y][bomba1->x+1] =' ';
            }

            // matar o jogador
            if(bomba1->x == *andarX && bomba1->y == *andarY){
                (*vidas)--;
                *andarX = 10;
                *andarY = 6;
            }

            if(bomba1->x == *andarX && bomba1->y-1 == *andarY){
                (*vidas)--;
                *andarX = 10;
                *andarY = 6;
            }

            if(bomba1->x == *andarX && bomba1->y+1 == *andarY){
                (*vidas)--;
                *andarX = 10;
                *andarY = 6;
            }

            if(bomba1->x-1 == *andarX && bomba1->y == *andarY){
                (*vidas)--;
                *andarX = 10;
                *andarY = 6;
            }

            if(bomba1->x+1 == *andarX && bomba1->y == *andarY){
                (*vidas)--;
                *andarX = 10;
                *andarY = 6;
            }

            // matar inimigos
            for(int i=0;i<5;i++){
                if(inimigos[i].vivo ==0){
                    continue;
                }

                if(bomba1->x == inimigos[i].x && bomba1->y == inimigos[i].y){
                    inimigos[i].vivo = 0;
                }

                if(bomba1->x == inimigos[i].x && bomba1->y -1 == inimigos[i].y){
                    inimigos[i].vivo = 0;
                }

                if(bomba1->x == inimigos[i].x && bomba1->y+1 == inimigos[i].y){
                    inimigos[i].vivo = 0;
                }

                if(bomba1->x -1 ==inimigos[i].x && bomba1->y == inimigos[i].y){
                    inimigos[i].vivo = 0;
                }

                if (bomba1->x +1 == inimigos[i].x && bomba1->y == inimigos[i].y){
                    inimigos[i].vivo = 0;
                }
            }
        }
    }

    if (bomba1->explosao == 1){

        bomba1->tempoExplosao -= GetFrameTime();

        bomba1->tempoFrame += GetFrameTime();

        if(bomba1->tempoFrame >= 0.05f){
            bomba1->frameExplosao++;
            bomba1->tempoFrame = 0;
        }

        if(bomba1->frameExplosao > 11){
            bomba1->frameExplosao = 11;
        }

        if(bomba1->tempoExplosao <= 0){
            bomba1->explosao = 0;
        }
    }
}