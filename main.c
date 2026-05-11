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

void moverinimigo(char mapa[LINHAS][COLUNAS+1],inimigo *inimigo1, int andarX, int andarY, int *vivo){

    if(inimigo1->vivo == 0){
        return;
    }

    if(inimigo1->x == andarX && inimigo1->y == andarY){
        *vivo = 0;
    }

    inimigo1->tempoInimigo += GetFrameTime();

    if(inimigo1->tempoInimigo >= 0.5f){

        int direcao = rand()%4;

        if(direcao == 0 && mapa[inimigo1->y - 1][inimigo1->x] != '#' && mapa[inimigo1->y - 1][inimigo1->x] != '*'){
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

        if(inimigo1->x == andarX && inimigo1->y == andarY){
            *vivo = 0;
        }

        inimigo1->tempoInimigo = 0;
    }
}

void colocarbomba(bomba* bomba1, int andarX, int andarY){
    if(IsKeyPressed(KEY_SPACE) && bomba1->ativa == 0){

        bomba1->x = andarX;
        bomba1->y = andarY;

        bomba1->ativa = 1;

        bomba1->timer = 4.0f;
    }
}

void atualizarbomba(char mapa[LINHAS][COLUNAS + 1],bomba *bomba1,int andarX,int andarY,int *vivo,inimigo *inimigo1){

    if (bomba1->ativa == 1){
        bomba1->timer -= GetFrameTime();
            
        if (bomba1->timer <= 0){

            bomba1->ativa = 0;
            bomba1->explosao = 1;
            bomba1->tempoExplosao = 0.5f;

            // qubrar bloco com explosao
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

            // matar jogador
            if(bomba1->x == andarX && bomba1->y == andarY){
                *vivo = 0;
            }
            if(bomba1->x == andarX && bomba1->y-1 == andarY){
                *vivo=0;
            }
            if(bomba1->x == andarX && bomba1->y + 1 == andarY){
                *vivo=0;
            }
            if(bomba1->x-1 == andarX && bomba1->y == andarY){
                *vivo=0;
            }
            if(bomba1->x+1 == andarX && bomba1->y == andarY){
                *vivo=0;
            }

            // matar inimigo
            if(bomba1->x == inimigo1->x && bomba1->y == inimigo1->y){
                inimigo1->vivo = 0;
            }
            if(bomba1->x == inimigo1->x && bomba1->y-1 == inimigo1->y){
                inimigo1->vivo =0;
            }
            if(bomba1->x == inimigo1->x && bomba1->y+1 == inimigo1->y){
                inimigo1->vivo =0;
            }
            if(bomba1->x-1 == inimigo1->x && bomba1->y == inimigo1->y){
                inimigo1->vivo = 0;
            }
            if(bomba1->x+1 == inimigo1->x && bomba1->y == inimigo1->y){
                inimigo1->vivo =0;
            }
        }
    }

    if (bomba1->explosao == 1){
        bomba1->tempoExplosao -= GetFrameTime();
            
        if (bomba1->tempoExplosao <= 0){
            bomba1->explosao = 0;
        }
    }
}

void dmapa(char mapa[LINHAS][COLUNAS+1]){
    for (int y=0;y < LINHAS;y++){
        for (int x=0;x < COLUNAS;x++){
            // parede
            if (mapa[y][x]== '#') {
                DrawRectangle(
                    x * pixel,
                    y * pixel,
                    pixel,
                    pixel,
                    GRAY
                );
            }
            // bloco que qubra
            if (mapa[y][x] == '*'){
                DrawRectangle(
                    x * pixel,
                    y * pixel,
                    pixel,
                    pixel,
                    BROWN
                );
            }
}}}

void djogador(int x,int y){
    DrawRectangle(
        x * pixel,
        y * pixel,
        pixel,
        pixel,
        RED
    );
}

void dbomba(bomba bomba1){
    if (bomba1.ativa == 1){
        DrawRectangle(
            bomba1.x * pixel,
            bomba1.y * pixel,
            pixel,
            pixel,
            BLUE
        );
    }
}

void dexplosao(bomba bomba1){
    if (bomba1.explosao == 1){
        DrawRectangle(
            bomba1.x * pixel,
            bomba1.y * pixel,
            pixel,
            pixel,
            YELLOW
        );

        DrawRectangle(
            bomba1.x * pixel,
            (bomba1.y-1) * pixel,
            pixel,
            pixel,
            ORANGE
        );

        DrawRectangle(
            bomba1.x * pixel,
            (bomba1.y+1) * pixel,
            pixel,
            pixel,
            ORANGE
        );

        DrawRectangle(
            (bomba1.x-1) * pixel,
            bomba1.y * pixel,
            pixel,
            pixel,
            ORANGE
        );

        DrawRectangle(
            (bomba1.x+1) * pixel,
            bomba1.y * pixel,
            pixel,
            pixel,
            ORANGE
        );
    }
}

void dinimigo(inimigo inimigo1){
    if(inimigo1.vivo == 1){
        DrawRectangle(
            inimigo1.x * pixel,
            inimigo1.y * pixel,
            pixel,
            pixel,
            GREEN
        );
    }
}

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

    int vivo = 1;

    int andarX = 10;
    int andarY = 6;

    bomba bomba1;

    bomba1.ativa = 0;
    bomba1.explosao = 0;

    inimigo inimigo1;

    inimigo1.x = 15;
    inimigo1.y = 8;
    inimigo1.vivo = 1;
    inimigo1.tempoInimigo = 0;

    InitWindow(
        COLUNAS * pixel,
        LINHAS * pixel,
        "BomberMan"
    );

    SetTargetFPS(60);

    while(!WindowShouldClose() && vivo == 1){

        moverjogador(mapa,&andarX,&andarY);

        colocarbomba(&bomba1, andarX, andarY);

        atualizarbomba(mapa,&bomba1,andarX,andarY,&vivo,&inimigo1);

        moverinimigo(mapa,&inimigo1, andarX,andarY, &vivo);

        BeginDrawing();
        ClearBackground(BLACK);

        dmapa(mapa);

        djogador(andarX,andarY);

        dbomba(bomba1);

        dexplosao(bomba1);

        dinimigo(inimigo1);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}