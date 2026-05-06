#include "raylib.h"

#define pixel 64
#define LINHAS 13
#define COLUNAS 21

int main(){

    char mapa[LINHAS][COLUNAS + 1]={
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

        // RENDER
        BeginDrawing();
        ClearBackground(BLACK);

        for (int y = 0; y < LINHAS; y++) {
            for (int x = 0; x < COLUNAS; x++) {

                // parede
                if (mapa[y][x] == '#') {
                    DrawRectangle(
                        x * pixel,
                        y * pixel,
                        pixel,
                        pixel,
                        GRAY
                    );
                }

                // jogador
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

        EndDrawing();
    }

    CloseWindow();

    return 0;
}