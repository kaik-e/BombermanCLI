#include "raylib.h"
#include <stdlib.h>

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
    }
}

void atualizarbomba(char mapa[LINHAS][COLUNAS+1],bomba *bomba1,int *andarX,int *andarY,int *vidas,inimigo inimigos[5]){
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

void dmapa(char mapa[LINHAS][COLUNAS+1],Texture2D parede,Texture2D bloco, Texture2D chao,int offsetX,int offsetY){
    for (int y=0;y < LINHAS;y++){
        for (int x=0;x < COLUNAS;x++){

            if(mapa[y][x] == ' '){
                // chao
                float escalaChao = (float)pixel / chao.width;

                DrawTextureEx(
                    chao,
                    (Vector2){x * pixel + offsetX, y * pixel+ offsetY},
                    0.0f,
                    escalaChao,
                    WHITE
                );
            }
            // parede
            if (mapa[y][x]== '#') {

                float escalaParede = (float)pixel / parede.width;

                DrawTextureEx(
                    parede,
                    (Vector2){x * pixel + offsetX, y * pixel+ offsetY},
                    0.0f,
                    escalaParede,
                    WHITE
                );
            }
            // bloco que qubra
            if (mapa[y][x] == '*'){

                float escalaBloco = (float)pixel / bloco.width;

                DrawTextureEx(
                    bloco,
                    (Vector2){x * pixel + offsetX, y * pixel+ offsetY},
                    0.0f,
                    escalaBloco,
                    WHITE
                );
            }
}}}

void djogador(Texture2D jogador, int x,int y,int offsetX,int offsetY){
    DrawTextureEx(
        jogador,
        (Vector2){
            x * pixel - 8 + offsetX,y * pixel - 12 + offsetY},
        0.0f,
        0.17f,
        WHITE
    );
}

void dbomba(bomba bomba1,int offsetX,int offsetY){
    if (bomba1.ativa == 1){
        DrawRectangle(
            bomba1.x * pixel + offsetX,
            bomba1.y * pixel + offsetY,
            pixel,
            pixel,
            BLUE
        );
    }
}

void dexplosao(bomba bomba1, int offsetX, int offsetY){
    if (bomba1.explosao ==1){
        DrawRectangle(
            bomba1.x*pixel + offsetX,
            bomba1.y*pixel + offsetY,
            pixel,
            pixel,
            YELLOW
        );

        DrawRectangle(
            bomba1.x * pixel +offsetX,
            (bomba1.y-1) * pixel + offsetY,
            pixel,
            pixel,
            ORANGE
        );

        DrawRectangle(
            bomba1.x *pixel+ offsetX,
            (bomba1.y+1) *pixel+ offsetY,
            pixel,
            pixel,
            ORANGE
        );

        DrawRectangle(
            (bomba1.x-1)* pixel+offsetX,
            bomba1.y * pixel + offsetY,
            pixel,
            pixel,
            ORANGE
        );

        DrawRectangle(
            (bomba1.x+1) * pixel+ offsetX,
            bomba1.y * pixel+offsetY,
            pixel,
            pixel,
            ORANGE
        );
    }
}

void dinimigo(Texture2D inimigo, struct inimigo inimigo1,int offsetX, int offsetY){
    if(inimigo1.vivo == 1){
        DrawTextureEx(inimigo,(Vector2){inimigo1.x * pixel - 8 + offsetX,inimigo1.y * pixel - 12 + offsetY},
            0.0f,
            0.17f,
            WHITE
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

    int estadoJogo = 0;

    int fase=1;

    int vidas = 3;

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

    ToggleFullscreen();

    int larguraBloco = GetScreenWidth() / COLUNAS;
    int alturaBloco = GetScreenHeight() / LINHAS;

    pixel = larguraBloco;

    if(alturaBloco < pixel){
        pixel = alturaBloco;
}

    Texture2D menu = LoadTexture("menu.png.png");
    Texture2D jogador = LoadTexture("player.png");
    Texture2D inimigo = LoadTexture("inimigo.png");
    Texture2D faseCompleta = LoadTexture("fasecompleta.png");
    Texture2D parede = LoadTexture("parede.png");
    Texture2D bloco = LoadTexture("bloco.png");
    Texture2D chao = LoadTexture("chao.png");
    Texture2D telaFinal = LoadTexture("final.png");
    Texture2D gameOver = LoadTexture("gameover.png");

    SetTargetFPS(60);
    
    int offsetX =(GetScreenWidth() - (COLUNAS * pixel)) / 2;
    int offsetY =(GetScreenHeight() - (LINHAS * pixel))/ 2;

    while(!WindowShouldClose()){

        if(IsKeyPressed(KEY_K)){
            for(int i = 0; i < 5; i++){
                inimigos[i].vivo = 0;
            }
        }

        if(estadoJogo == 0){
            BeginDrawing();
            ClearBackground(BLACK);

            Rectangle source={
                0,
                0,
                menu.width,
                menu.height
            };

            Rectangle dest= {
                0,
                0,
                GetScreenWidth(),
                GetScreenHeight()
            };

            DrawTexturePro(
                menu,
                source,
                dest,
                (Vector2){0,0},
                0.0f,
                WHITE
            );

            Vector2 mouse=GetMousePosition();

            Rectangle botaojogar={
                GetScreenWidth()/2 - 220,
                GetScreenHeight()/2 + 10,
                450,
                70
            };

            if(CheckCollisionPointRec(mouse,botaojogar)){
                DrawRectangleRoundedLines(
                    botaojogar,
                    0.3f,
                    10,
                    GOLD
                );
            }

            if(CheckCollisionPointRec(mouse, botaojogar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                estadoJogo =1;
            }

            Rectangle botaoSair={
                GetScreenWidth()/2 - 220,
                GetScreenHeight()/2 + 185,
                450,
                70
            };


            if(CheckCollisionPointRec(mouse, botaoSair)){
                DrawRectangleRoundedLines(
                    botaoSair,
                    0.3f,
                    10, 
                    DARKBLUE
                );

                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){

                    CloseWindow();
                }
            }

            EndDrawing();
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
                estadoJogo = 3;
            }
            else{
                estadoJogo = 2;
            }
        }

        if(estadoJogo == 2){
            BeginDrawing();

            ClearBackground(BLACK);

            dmapa(mapa,parede,bloco,chao,offsetX,offsetY);

            djogador(jogador,andarX,andarY,offsetX,offsetY);

            dbomba(bomba1,offsetX,offsetY);

            dexplosao(bomba1,offsetX,offsetY);

            for(int i=0;i <5;i++){
                dinimigo(inimigo,inimigos[i],offsetX,offsetY);
            }

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
                DrawRectangleRoundedLines(
                    botaoProximaFase,
                    0.3f,
                    10,
                    GREEN
                );

                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    fase++;

                    estadoJogo = 1;

                    andarX = 10;
                    andarY = 6;
                }
            }

            if(CheckCollisionPointRec(mouse, botaoSair)){           
                DrawRectangleRoundedLines(
                    botaoSair,
                    0.3f,
                    10,
                    RED
                );

                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    CloseWindow();
                }
            }

            EndDrawing();
            continue;
        }

        if(estadoJogo == 3){
            BeginDrawing();

            ClearBackground(BLACK);

            dmapa(mapa,parede,bloco,chao,offsetX,offsetY);

            djogador(jogador, andarX, andarY,offsetX, offsetY);

            dbomba(bomba1, offsetX, offsetY);

            dexplosao(bomba1, offsetX, offsetY);

            for(int i = 0; i < 5; i++){
                dinimigo(inimigo,inimigos[i],offsetX,offsetY);
            }

            DrawRectangle(
                0,
                0,
                GetScreenWidth(),
                GetScreenHeight(),
                Fade(BLACK, 0.5f)
            );

            float escalaFinal = 0.7f;

            float larguraFinal = telaFinal.width * escalaFinal;
            float alturaFinal = telaFinal.height * escalaFinal;

            float posXFinal = (GetScreenWidth() - larguraFinal) / 2;
            float posYFinal = (GetScreenHeight() - alturaFinal) / 2;

            Rectangle source = {
                0,
                0,
                telaFinal.width,
                telaFinal.height
            };

            Rectangle dest = {
                0,
                0,
                GetScreenWidth(),
                GetScreenHeight()
            };

            DrawTexturePro(
                telaFinal,
                source,
                dest,
                (Vector2){0,0},
                0.0f,
                WHITE
            );

            EndDrawing();

            continue;
        }

        if(estadoJogo == 4){
            BeginDrawing();

            ClearBackground(BLACK);

            Rectangle source={
                0,
                0,
                gameOver.width,
                gameOver.height
            };

            Rectangle dest={
                0,
                0,
                GetScreenWidth(),
                GetScreenHeight()
            };

            DrawTexturePro(
                gameOver,
                source,
                dest,
                (Vector2){0,0},
                0.0f,
                WHITE
            );

            Vector2 mouse=GetMousePosition();

            Rectangle botaoReiniciar={
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

            if(CheckCollisionPointRec(mouse, botaoReiniciar)){
                DrawRectangleRoundedLines(
                    botaoReiniciar,
                    0.3f,
                    10,
                    YELLOW
                );

                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    vidas = 3;

                    fase = 1;
                    faseatual = 1;

                    andarX = 10;
                    andarY = 6;

                    estadoJogo = 1;

                    carregarMapa(mapa,mapa);

                    inimigos[0].x = 15;
                    inimigos[0].y = 8;
                    inimigos[0].vivo = 1;

                    for(int i=1;i<5;i++){
                        inimigos[i].vivo = 0;
                    }

                    bomba1.ativa = 0;
                    bomba1.explosao = 0;
                }
            }

            if(CheckCollisionPointRec(mouse, botaoMenu)){
                DrawRectangleRoundedLines(
                    botaoMenu,
                    0.3f,
                    10,
                    DARKBLUE
                );

                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    vidas = 3;

                    fase = 1;
                    faseatual = 1;

                    andarX = 10;
                    andarY = 6;

                    estadoJogo = 0;

                    carregarMapa(mapa,mapa);

                    inimigos[0].x = 15;
                    inimigos[0].y = 8;
                    inimigos[0].vivo = 1;

                    for(int i=1;i<5;i++){
                        inimigos[i].vivo = 0;
                    }

                    bomba1.ativa = 0;
                    bomba1.explosao = 0;
                }
            }

            EndDrawing();
            continue;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        dmapa(mapa,parede,bloco,chao,offsetX,offsetY);

        djogador(jogador, andarX, andarY,offsetX, offsetY);

        dbomba(bomba1, offsetX, offsetY);

        dexplosao(bomba1, offsetX, offsetY);

        for(int i = 0; i < 5; i++){
            dinimigo(inimigo,inimigos[i],offsetX,offsetY);
        }

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

    CloseWindow();

    return 0;
    }
