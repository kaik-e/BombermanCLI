#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

int pixel = 64;
#define LINHAS 13
#define COLUNAS 21

typedef struct bomba{
    int x;
    int y;
    int ativa;
    float timer;
    int explosao;
    float tempoExplosao;

    int frameExplosao;
    float tempoFrame;

    int frameBomba;
    float tempoBomba;
} bomba;

typedef struct inimigo{
    int x;
    int y;
    int vivo;
    float tempoInimigo;
}inimigo;

typedef struct score{
    float tempo;
    struct score *prox;
}score;

void adicionarScore(score **lista, float tempo){

    score *novo = malloc(sizeof(score));

    novo->tempo = tempo;
    novo->prox = *lista;

    *lista = novo;
}

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

    int estadoJogo = 0;

    int fase=1;

    int vidas = 3;

    float tempoJogo = 0;
    float topScore = 9999;

    score *listaScores = NULL;

    int andarX=10;
    int andarY=6;

    int faseatual=1;

    bomba bomba1;

    bomba1.ativa=0;
    bomba1.explosao=0;

    bomba1.frameExplosao = 0;
    bomba1.tempoFrame = 0;

    bomba1.frameBomba = 0;
    bomba1.tempoBomba = 0;

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

    ToggleFullscreen();

    int larguraBloco = GetScreenWidth() / COLUNAS;
    int alturaBloco = GetScreenHeight() / LINHAS;

    pixel = larguraBloco;

    if(alturaBloco < pixel){
        pixel = alturaBloco;
}
    Texture2D menu = LoadTexture("assets/menu.png.png");
    Texture2D jogador = LoadTexture("assets/player.png");
    Texture2D inimigo = LoadTexture("assets/inimigo.png");
    Texture2D telaFinal = LoadTexture("assets/final.png");
    Texture2D gameOver = LoadTexture("assets/gameover.png");
    Texture2D parede = LoadTexture("assets/parede.png");
    Texture2D bloco = LoadTexture("assets/bloco.png");
    Texture2D chao = LoadTexture("assets/chao.png");
    Texture2D faseCompleta = LoadTexture("assets/fasecompleta.png");
    Texture2D explosao = LoadTexture("assets/explosao.png");
    Texture2D bombaTex = LoadTexture("assets/bomba.png");

    FILE *arquivo = fopen("topscore.txt", "r");

    if(arquivo != NULL){
        fscanf(arquivo, "%f", &topScore);
        fclose(arquivo);
    }

    SetTargetFPS(120);
    
    int offsetX =(GetScreenWidth() - (COLUNAS * pixel)) / 2;
    int offsetY =(GetScreenHeight() - (LINHAS * pixel))/ 2;

    while(!WindowShouldClose()){

        if(estadoJogo == 1){
            tempoJogo += GetFrameTime();
        }

        if(IsKeyPressed(KEY_K)){
            for(int i = 0; i < 5; i++){
                inimigos[i].vivo = 0;
            }
        }

        if(estadoJogo == 0){
            desenharMenu(menu);

            Vector2 mouse = GetMousePosition();

            Rectangle botaojogar={
                GetScreenWidth()/2 - 220,
                GetScreenHeight()/2 + 10,
                450,
                70
            };

            if(CheckCollisionPointRec(mouse, botaojogar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                resetarJogo(mapa,&bomba1,inimigos,&vidas,&fase,&faseatual,&andarX,&andarY,&tempoJogo);

                estadoJogo = 1;
            }

            Rectangle botaoSair = {
                GetScreenWidth()/2 - 220,
                GetScreenHeight()/2 + 185,
                450,
                70
            };

            if(CheckCollisionPointRec(mouse, botaoSair) &&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                CloseWindow();
            }

            Rectangle botaoCreditosinicio={
                GetScreenWidth()/2 - 220,
                GetScreenHeight()/2 + 100,
                450,
                70
            };

            if(CheckCollisionPointRec(mouse, botaoCreditosinicio) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){

                estadoJogo = 5;
            }

            continue;
        }

        

        moverjogador(mapa,&andarX,&andarY);

        colocarbomba(&bomba1, andarX, andarY);

        atualizarbomba(mapa,&bomba1,&andarX,&andarY,&vidas,inimigos);

        for(int i=0;i<5;i++){
           moverinimigo(mapa,&inimigos[i],&andarX,&andarY,&vidas);
        }

        if (fase==2 && faseatual != 2){
            faseatual=2;
            carregarMapa(mapa,mapa2);

            inimigos[0].x = 14;
            inimigos[0].y = 8;
            inimigos[0].vivo=1;

            inimigos[1].x = 8;
            inimigos[1].y = 9;
            inimigos[1].vivo=1;

            inimigos[2].vivo = 0;
            inimigos[3].vivo = 0;
            inimigos[4].vivo = 0;

            bomba1.ativa=0;
            bomba1.explosao=0;
        }

        if(fase==3 && faseatual != 3){
            faseatual=3;
            carregarMapa(mapa,mapa3);

            inimigos[0].x=2;
            inimigos[0].y=1;

            inimigos[1].x=7;
            inimigos[1].y=3;

            inimigos[2].x=13;
            inimigos[2].y=5;

            inimigos[3].x=17;
            inimigos[3].y=7;

            inimigos[4].x=18;
            inimigos[4].y=11;

            for(int i=0;i<5;i++){
                inimigos[i].vivo=1;
            }

            bomba1.ativa = 0;
            bomba1.explosao = 0;

        }

        int inimigosVivos = 0;

        for(int i=0;i<5;i++){
            if(inimigos[i].vivo == 1){
                inimigosVivos++;
            }
        }

        if(vidas <= 0){
            estadoJogo = 4;
        }

        if(inimigosVivos == 0 && estadoJogo == 1){
            if(fase == 3){
                adicionarScore(&listaScores, tempoJogo);

                if(tempoJogo < topScore){
                    topScore = tempoJogo;

                    FILE *arquivo = fopen("topscore.txt", "w");

                    if(arquivo != NULL){
                        fprintf(arquivo, "%.2f", topScore);
                        fclose(arquivo);
                    }
                }

                estadoJogo = 3;
            }
            else{
                estadoJogo = 2;
            }
        }

        if(estadoJogo == 2){
            desenharGameplay(mapa, parede, bloco, chao, jogador, inimigo, bombaTex, explosao, bomba1, inimigos, 
                andarX, andarY, offsetX, offsetY);

            DrawRectangle(
                0,
                0,
                GetScreenWidth(),
                GetScreenHeight(),
                Fade(BLACK, 0.5f)
            );

            float escala = 0.55f;

            float larguraBanner = faseCompleta.width * escala;
            float alturaBanner = faseCompleta.height * escala;

            float posX = (GetScreenWidth() - larguraBanner) / 2;
            float posY = (GetScreenHeight() - alturaBanner) / 2;

            DrawTextureEx(
                faseCompleta,
                (Vector2){posX, posY},
                0.0f,
                escala,
                WHITE
            );
            
            Vector2 mouse = GetMousePosition();

            Rectangle botaoProximaFase = {
                GetScreenWidth()/2 - 260,
                GetScreenHeight()/2 + 58,
                248,
                60
            };

            Rectangle botaoSair = {
                GetScreenWidth()/2 + 18,
                GetScreenHeight()/2 + 58,
                245,
                60
            };
            
            if(CheckCollisionPointRec(mouse, botaoProximaFase)){
                desenharBotao(botaoProximaFase,GREEN);

                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    fase++;

                    estadoJogo = 1;

                    andarX = 10;
                    andarY = 6;
                }
            }

            if(CheckCollisionPointRec(mouse, botaoSair)){           
                desenharBotao(botaoSair,RED);

                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    CloseWindow();
                }
            }

            EndDrawing();
            continue;
        }

        if(estadoJogo == 3){
            desenharTelaFinal(telaFinal,parede,bloco,chao,jogador,inimigo,bombaTex,explosao,mapa,bomba1,inimigos,andarX,andarY,
                offsetX,offsetY,tempoJogo,topScore);

            Vector2 mouse = GetMousePosition();

            Rectangle botaoMenu={
                GetScreenWidth()/2 - 288,
                GetScreenHeight()/2 +198,
                585,
                70
            };

            Rectangle botaoCreditos = {
                GetScreenWidth()/2 - 288,
                GetScreenHeight()/2 +282,
                585,
                70
            };

            if(CheckCollisionPointRec(mouse, botaoMenu) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                resetarJogo(mapa,&bomba1,inimigos,&vidas,&fase,&faseatual,&andarX,&andarY,&tempoJogo);

                estadoJogo = 0;
            }

            if(CheckCollisionPointRec(mouse, botaoCreditos) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){

                estadoJogo = 5;
            }
            continue;
        }

                if(estadoJogo == 4){
                    desenharGameOver(gameOver);

                    Vector2 mouse = GetMousePosition();

                    Rectangle botaoReiniciar = {
                        GetScreenWidth()/2 - 220,
                        GetScreenHeight()/2 + 100,
                        450,
                        70
                    };

                    Rectangle botaoMenu = {
                        GetScreenWidth()/2 - 220,
                        GetScreenHeight()/2 + 185,
                        450,
                        70
                    };

                    if(CheckCollisionPointRec(mouse, botaoReiniciar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        resetarJogo(mapa,&bomba1,inimigos, &vidas,&fase,&faseatual,&andarX,&andarY,&tempoJogo);

                        estadoJogo = 1;
                    }

                    if(CheckCollisionPointRec(mouse, botaoMenu) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        resetarJogo(mapa,&bomba1,inimigos, &vidas,&fase,&faseatual,&andarX,&andarY,&tempoJogo);

                        estadoJogo = 0;
                    }

                    continue;
                }

        if(estadoJogo==5){
            desenharCreditos();

            if(IsKeyPressed(KEY_ENTER)){
                estadoJogo = 0;
            }

            continue;
        }

        desenharGameplay(mapa,parede,bloco,chao, jogador,inimigo,bombaTex,explosao,bomba1, inimigos,andarX,andarY,
            offsetX,offsetY);
            
        EndDrawing();
    }

    UnloadTexture(menu);
    UnloadTexture(jogador);
    UnloadTexture(inimigo);
    UnloadTexture(faseCompleta);
    UnloadTexture(parede);
    UnloadTexture(bloco);
    UnloadTexture(chao);
    UnloadTexture(telaFinal);
    UnloadTexture(gameOver);
    UnloadTexture(explosao);
    UnloadTexture(bombaTex);

    CloseWindow();

    score *atual = listaScores;

    while(atual != NULL){
        score *temp = atual;
        atual = atual->prox;
        free(temp);
    }

    return 0;
    }
