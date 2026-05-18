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

    if(inimigo1->tempoInimigo >= 0.7f){
        int mexeu = 0;

        if(andarX>inimigo1->x && mapa[inimigo1->y][inimigo1->x+1] != '#' && mapa[inimigo1->y][inimigo1->x + 1] != '*'){
            inimigo1->x++;
            mexeu=1;
        }

        else if(andarX < inimigo1->x && mapa[inimigo1->y][inimigo1->x-1] != '#' && mapa[inimigo1->y][inimigo1->x-1] != '*'){
            inimigo1->x--;
            mexeu=1;
        }

        else if(andarY > inimigo1->y && mapa[inimigo1->y+ 1][inimigo1->x] != '#' && mapa[inimigo1->y+1][inimigo1->x] != '*'){
            inimigo1->y++;
            mexeu=1;
        }

        else if(andarY < inimigo1->y && mapa[inimigo1->y-1][inimigo1->x] != '#' && mapa[inimigo1->y -1][inimigo1->x] != '*'){
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

        if(inimigo1->x == andarX && inimigo1->y == andarY){
            *vivo = 0;
        }

        inimigo1->tempoInimigo = 0;
    }
}

void colocarbomba(bomba* bomba1, int andarX,int andarY){
    if(IsKeyPressed(KEY_SPACE) && bomba1->ativa == 0){

        bomba1->x = andarX;
        bomba1->y = andarY;

        bomba1->ativa = 1;

        bomba1->timer = 4.0f;
    }
}

void atualizarbomba(char mapa[LINHAS][COLUNAS+1],bomba *bomba1,int andarX,int andarY,int *vivo,inimigo inimigos[5]){
    if (bomba1->ativa == 1){
        bomba1->timer -= GetFrameTime();
            
        if (bomba1->timer <= 0){

            bomba1->ativa = 0;
            bomba1->explosao = 1;
            bomba1->tempoExplosao = 0.5f;

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
            if(bomba1->x == andarX && bomba1->y == andarY){
                *vivo = 0;
            }

            if(bomba1->x == andarX && bomba1->y-1 == andarY){
                *vivo = 0;
            }

            if(bomba1->x == andarX && bomba1->y+1 == andarY){
                *vivo = 0;
            }

            if(bomba1->x-1 == andarX && bomba1->y == andarY){
                *vivo = 0;
            }

            if(bomba1->x+1 == andarX && bomba1->y == andarY){
                *vivo = 0;
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

    if (bomba1->explosao== 1){
        bomba1->tempoExplosao -= GetFrameTime();
            
        if(bomba1->tempoExplosao <=0){
            bomba1->explosao = 0;
        }
    }
}

void carregarMapa(char mapa[LINHAS][COLUNAS+1],char novaFase[LINHAS][COLUNAS+1]){
    for(int y=0;y <LINHAS;y++){
        for(int x=0;x < COLUNAS + 1;x++){
            mapa[y][x] = novaFase[y][x];
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
        "#    * *  *    *    #",
        "#     **     *   *  #",
        "#   * *   *  *  **  #",
        "#    *  * *     *   #",
        "#  *    *    *   *  #",
        "# *  *    *  *  *   #",
        "#* **  *   ** *     #",
        "#  *   * *       *  #",
        "#    *  *    *   *  #",
        "#####################"
    };

    char mapa2[LINHAS][COLUNAS+1]={
        "#####################",
        "#   *   *     ***   #",
        "#  *    *  *  *  *  #",
        "#  * *    *    *    #",
        "# *   ** *   *   *  #",
        "#   * *   *   **    #",
        "#  * *  * *     *   #",
        "#  *    *    *   *  #",
        "# *  *    *  *  *   #",
        "#* *  *   *  * *  * #",
        "#  *  *  *   *   *  #",
        "#    *  *    *  **  #",
        "#####################"
    };

    char mapa3[LINHAS][COLUNAS+1]={
        "#####################",
        "#*  *   *  ** ***   #",
        "#  * *  *  *  * * * #",
        "#  * *    *    *  * #",
        "# *   ** *   *   *  #",
        "#   * *   *  ** * * #",
        "# ** *  * * *   **  #",
        "#  *  * * *  *   *  #",
        "# *  *    *  *  *   #",
        "#*  *  *  **  *   * #",
        "#  * *   **   *  *  #",
        "# *  *  *  * *   *  #",
        "#####################"
    };

    int fase=1;

    int vivo=1;

    int andarX=10;
    int andarY=6;

    int faseatual=1;

    bomba bomba1;

    bomba1.ativa=0;
    bomba1.explosao=0;

    inimigo inimigos[5];

    for(int i=0;i<5;i++){
        inimigos[i].vivo=0;
        inimigos[i].tempoInimigo=0;
    }

    inimigos[0].x = 15;
    inimigos[0].y = 8;
    inimigos[0].vivo = 1;

    InitWindow(
        COLUNAS * pixel,
        LINHAS * pixel,
        "BomberMan"
    );

    SetTargetFPS(60);

    while(!WindowShouldClose() && vivo == 1){

        moverjogador(mapa,&andarX,&andarY);

        colocarbomba(&bomba1, andarX, andarY);

        atualizarbomba(mapa,&bomba1,andarX,andarY,&vivo, inimigos);

        for(int i=0;i<5;i++){
            moverinimigo(mapa,&inimigos[i],andarX,andarY,&vivo);
        }

        int inimigosVivos = 0;

        for(int i=0;i<5;i++){
            if(inimigos[i].vivo == 1){
                inimigosVivos++;
            }
        }

        if(inimigosVivos == 0){
            fase++;

            andarX=10;
            andarY=6;
        }

        if (fase==2 && faseatual != 2){
            faseatual=2;
            carregarMapa(mapa,mapa2);

            inimigos[0].x=15;
            inimigos[0].y=8;
            inimigos[0].vivo=1;

            inimigos[1].x=3;
            inimigos[1].y=9;
            inimigos[1].vivo=1;

            bomba1.ativa=0;
            bomba1.explosao=0;
        }

        if(fase==3 && faseatual != 3){
            faseatual=3;
            carregarMapa(mapa,mapa3);

            inimigos[0].x=1;
            inimigos[0].y=1;

            inimigos[1].x= 5;
            inimigos[1].y=3;

            inimigos[2].x=10;
            inimigos[2].y=5;

            inimigos[3].x=15;
            inimigos[3].y=7;

            inimigos[4].x=18;
            inimigos[4].y=10;

            for(int i=0;i<5;i++){
                inimigos[i].vivo=1;
            }

            bomba1.ativa = 0;
            bomba1.explosao = 0;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        dmapa(mapa);

        djogador(andarX,andarY);

        dbomba(bomba1);

        dexplosao(bomba1);

        for(int i = 0; i < 5; i++){
            dinimigo(inimigos[i]);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}