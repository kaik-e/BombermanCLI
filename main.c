#include "raylib.h"

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

int main(){

    char mapa[LINHAS][COLUNAS+1]={
    "#####################",
    "#                   #",
    "#                   #",  
    "#                   #",
    "#                   #",
    "#                   #",
    "#                   #",
    "#                   #",
    "#                   #",
    "#                   #",
    "#                   #",
    "#                   #",
    "#####################"
    };

    int andarX = 10;
    int andarY = 6;

    bomba bomba1;

    bomba1.ativa=0;
    bomba1.explosao = 0;

    InitWindow(COLUNAS*pixel, LINHAS*pixel, "BomberMan");

    SetTargetFPS(60);

    while(!WindowShouldClose()){

        if(IsKeyPressed(KEY_W) && mapa[andarY-1][andarX] != '#'){
            andarY--;
        }
        if(IsKeyPressed(KEY_S) && mapa[andarY+1][andarX] != '#'){
            andarY++;
        }
        if (IsKeyPressed(KEY_A) && mapa[andarY][andarX-1] != '#'){
            andarX--;
        }
        if (IsKeyPressed(KEY_D) && mapa[andarY][andarX+1] != '#'){
            andarX++;   
        }

        if (IsKeyPressed(KEY_SPACE)) {

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
            }
        }


        if (bomba1.explosao == 1){
            bomba1.tempoExplosao -= GetFrameTime();
            
            if (bomba1.tempoExplosao <= 0){
                bomba1.explosao=0;
            }
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

        EndDrawing();
    }

    CloseWindow();

    return 0;
}