#include "raylib.h"
#include <stdlib.h>

#define pixel 64
#define LINHAS 13
#define COLUNAS 21

typedef struct bomba{
    int x;
    int y;
    int ativa;
    float timer;
    int explosao;
    float tempoExplosao;
}bomba;

typedef struct inimigo{
    int x;
    int y;
    int vivo;
    float tempoInimigo;
}inimigo;

int main(){

    char mapa[LINHAS][COLUNAS+1]={
    "#####################",
    "#   *   *     ***   #",
    "#  *    *  *  *     #",  
    "#    *    *    *    #",
    "#     **     *   *  #",
    "#   * *   *         #",
    "#    *  * *     *   #",
    "#  *    *    *   *  #",
    "# *  *    *  *  *   #",
    "#*     *      *     #",
    "#  *     *       *  #",
    "#    *  *    *      #",
    "#####################"
    };

    int vivo =1;

    int andarX = 10;
    int andarY = 6;

    bomba bomba1;

    inimigo inimigo1;
    inimigo1.x = 15;
    inimigo1.y = 8;
    inimigo1.vivo = 1;
    inimigo1.tempoInimigo = 0;

    bomba1.ativa=0;
    bomba1.explosao = 0;

    InitWindow(COLUNAS*pixel, LINHAS*pixel, "BomberMan");

    SetTargetFPS(60);

    while(!WindowShouldClose() && vivo==1){

        if(IsKeyPressed(KEY_W) && mapa[andarY-1][andarX] != '#' && mapa[andarY-1][andarX] != '*'){
            andarY--;
        }
        if(IsKeyPressed(KEY_S) && mapa[andarY+1][andarX] != '#' && mapa[andarY+1][andarX] != '*'){
            andarY++;
        }
        if (IsKeyPressed(KEY_A) && mapa[andarY][andarX-1] != '#' && mapa[andarY][andarX-1] != '*'){
            andarX--;
        }
        if (IsKeyPressed(KEY_D) && mapa[andarY][andarX+1] != '#' && mapa[andarY][andarX+1] != '*'){
            andarX++;   
        }

        if (IsKeyPressed(KEY_SPACE) && mapa[bomba1.y][bomba1.x] != '*') {

            bomba1.x = andarX;
            bomba1.y = andarY;
            bomba1.ativa = 1;
            bomba1.timer= 4.0f;
        }

         if (bomba1.ativa == 1){
            bomba1.timer -= GetFrameTime();
            
            if (bomba1.timer <= 0){
                bomba1.ativa = 0;

                bomba1.explosao = 1;

                bomba1.tempoExplosao = 0.5f;

                if(mapa[bomba1.y-1][bomba1.x] == '*'){
                    mapa[bomba1.y-1][bomba1.x]=' ';
                } if (mapa[bomba1.y+1][bomba1.x] == '*'){
                    mapa[bomba1.y+1][bomba1.x] = ' ';
                } if(mapa[bomba1.y][bomba1.x-1] == '*'){
                    mapa[bomba1.y][bomba1.x-1] = ' ';
                } if(mapa[bomba1.y][bomba1.x+1] == '*'){
                    mapa[bomba1.y][bomba1.x+1] = ' ';
                }

                if(bomba1.x ==  andarX && bomba1.y == andarY){
                    vivo = 0;
                } if(bomba1.x ==andarX && bomba1.y-1 == andarY){
                    vivo = 0;
                }if(bomba1.x ==andarX && bomba1.y+1 == andarY){
                    vivo = 0;
                } if(bomba1.x-1 == andarX && bomba1.y == andarY){
                    vivo = 0;
                } if(bomba1.x+1 == andarX && bomba1.y == andarY){
                    vivo = 0;
                }

                if (bomba1.x == inimigo1.x && bomba1.y == inimigo1.y){
                    inimigo1.vivo = 0;
                }
                if (bomba1.x == inimigo1.x && bomba1.y-1 == inimigo1.y){
                    inimigo1.vivo = 0;
                }
                if(bomba1.x == inimigo1.x && bomba1.y+1 == inimigo1.y){
                    inimigo1.vivo = 0;
                }
                if(bomba1.x-1 == inimigo1.x && bomba1.y == inimigo1.y){
                    inimigo1.vivo = 0;
                }
                if(bomba1.x+1 == inimigo1.x && bomba1.y == inimigo1.y){
                    inimigo1.vivo = 0;
                }
            }
        }

        if (bomba1.explosao == 1){
            bomba1.tempoExplosao -= GetFrameTime();
            
            if (bomba1.tempoExplosao <= 0){
                bomba1.explosao=0;
            }
        }

        inimigo1.tempoInimigo += GetFrameTime();

        if(inimigo1.tempoInimigo >= 0.5f){
            int direcao = rand() % 4;

            if(direcao == 0 && mapa[inimigo1.y-1][inimigo1.x] != '#' && mapa[inimigo1.y-1][inimigo1.x] != '*'){
                inimigo1.y--;
            }

            if(direcao == 1 && mapa[inimigo1.y+1][inimigo1.x] != '#' && mapa[inimigo1.y+1][inimigo1.x] != '*'){
                inimigo1.y++;
            }

            if(direcao == 2 && mapa[inimigo1.y][inimigo1.x-1] != '#' && mapa[inimigo1.y][inimigo1.x-1] != '*'){
                inimigo1.x--;
            }

            if(direcao == 3 && mapa[inimigo1.y][inimigo1.x+1] != '#' && mapa[inimigo1.y][inimigo1.x+1] != '*'){
                inimigo1.x++;
            }
            inimigo1.tempoInimigo = 0;
        }

        if(inimigo1.x == andarX && inimigo1.y == andarY){
            vivo = 0;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (int y = 0; y < LINHAS; y++) {
            for (int x = 0; x < COLUNAS; x++) {

                if (mapa[y][x] == '#') {
                    DrawRectangle(
                        x * pixel,
                        y * pixel,
                        pixel,
                        pixel,
                        GRAY
                    );
                }

                if (mapa[y][x] == '*') {
                    DrawRectangle(
                        x * pixel,
                        y * pixel,
                        pixel,
                        pixel,
                        BROWN
                    );
                }

                if (x == andarX && y == andarY) {

                    DrawRectangle(
                        x * pixel,
                        y * pixel,
                        pixel,
                        pixel,
                        RED
                    );
                }
            }
        }

        if (bomba1.ativa==1){

            DrawRectangle(
                bomba1.x * pixel,
                bomba1.y * pixel,
                pixel,
                pixel,
                BLUE
            );
        }

        if (bomba1.explosao==1){
            DrawRectangle(
                bomba1.x *pixel,
                bomba1.y*pixel,
                pixel,
                pixel,
                YELLOW
            );


            DrawRectangle(
                bomba1.x*pixel,
                (bomba1.y-1)*pixel,
                pixel,
                pixel,
                ORANGE
            );

            DrawRectangle(
                bomba1.x* pixel,
                (bomba1.y+1) * pixel,
                pixel,
                pixel,
                ORANGE
            );


            DrawRectangle(
                (bomba1.x-1)*pixel,
                bomba1.y*pixel,
                pixel,
                pixel,
                ORANGE
            );


            DrawRectangle(
                (bomba1.x+1)*pixel,
                bomba1.y*pixel,
                pixel,
                pixel,
                ORANGE
            );
        }

        if(inimigo1.vivo == 1){

        DrawRectangle(
            inimigo1.x * pixel,
            inimigo1.y * pixel,
            pixel,
            pixel,
            GREEN
        );
    }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}