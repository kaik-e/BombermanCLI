#include "render.h"

extern int pixel;

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

void dbomba(Texture2D bombaTex, bomba bomba1, int offsetX, int offsetY){

    if(bomba1.ativa == 1){

        int frameWidth = bombaTex.width / 3;
        int frameHeight = bombaTex.height;

        Rectangle source = {
            bomba1.frameBomba * frameWidth,
            0,
            frameWidth,
            frameHeight
        };

        Rectangle dest = {
            bomba1.x * pixel - 10 + offsetX,
            bomba1.y * pixel - 10 + offsetY,
            pixel + 20,
            pixel + 20
        };

        DrawTexturePro(
            bombaTex,
            source,
            dest,
            (Vector2){0,0},
            0.0f,
            WHITE
        );
    }
}

void desenharFrameExplosao(Texture2D explosao, int frame, int x, int y, int offsetX, int offsetY){

    int frameWidth = explosao.width / 6;
    int frameHeight = explosao.height / 2;

    int coluna = frame % 6;
    int linha = frame / 6;

    Rectangle source = {
        coluna * frameWidth,
        linha * frameHeight,
        frameWidth,
        frameHeight
    };

    Rectangle dest = {
        x * pixel + offsetX,
        y * pixel + offsetY,
        pixel,
        pixel
    };

    DrawTexturePro(
        explosao,
        source,
        dest,
        (Vector2){0,0},
        0.0f,
        WHITE
    );
}

void dexplosao(Texture2D explosao, bomba bomba1, int offsetX, int offsetY){

    if(bomba1.explosao == 1){
        desenharFrameExplosao(explosao, bomba1.frameExplosao,bomba1.x, bomba1.y,offsetX, offsetY);

        desenharFrameExplosao(explosao, bomba1.frameExplosao,bomba1.x, bomba1.y - 1, offsetX, offsetY);

        desenharFrameExplosao(explosao, bomba1.frameExplosao,bomba1.x, bomba1.y + 1,offsetX, offsetY);

        desenharFrameExplosao(explosao, bomba1.frameExplosao,bomba1.x - 1, bomba1.y,offsetX, offsetY);

        desenharFrameExplosao(explosao, bomba1.frameExplosao,bomba1.x + 1, bomba1.y,offsetX, offsetY);
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


void desenharCreditos(){

    BeginDrawing();
    ClearBackground(BLACK);

    DrawText(
        "CREDITOS",
        GetScreenWidth()/ 2- 180,
        120,
        60,
        GOLD
    );

    DrawText(
        "Programacao:",
        200,
        260,
        40,
        WHITE
    );

    DrawText(
        "Luis Felipe, Hugo e Kaike",
        520,
        260,
        40,
        YELLOW
    );

    DrawText(
        "Pixel Arts:",
        200,
        340,
        40,
        WHITE
    );

    DrawText(
        "Luis Felipe",
        520,
        340,
        40,
        YELLOW
    );

    DrawText(
        "Framework:",
        200,
        420,
        40,
        WHITE
    );

    DrawText(
        "Raylib",
        520,
        420,
        40,
        YELLOW
    );

    DrawText(
        "Obrigado por jogar!",
        GetScreenWidth() / 2-240,
        600,
        50,
        GREEN
    );

    DrawText(
        "Pressione ENTER para voltar ao menu!",
        GetScreenWidth()/ 2-330,
        720,
        30,
        LIGHTGRAY
    );

    EndDrawing();
}

void desenharBotao(Rectangle botao,Color cor){
    Vector2 mouse = GetMousePosition();

    if(CheckCollisionPointRec(mouse, botao)){
        DrawRectangleRoundedLines(
            botao,
            0.3f,
            10,
            cor
        );
    }
}

void desenharMenu(Texture2D menu){

    BeginDrawing();
    ClearBackground(BLACK);

    Rectangle source={
        0,
        0,
        menu.width,
        menu.height
    };

    Rectangle dest={
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

    Vector2 mouse = GetMousePosition();

    Rectangle botaojogar ={
        GetScreenWidth() /2-220,
        GetScreenHeight() /2+ 0,
        450,
        70
    };

    if(CheckCollisionPointRec(mouse,botaojogar)){
        desenharBotao(botaojogar, GOLD);
    }

    Rectangle botaoSair = {
        GetScreenWidth()/ 2-220,
        GetScreenHeight()/2+185,
        450,
        70
    };

    if(CheckCollisionPointRec(mouse,botaoSair)){
        desenharBotao(botaoSair, DARKBLUE);
    }

    Rectangle botaoCreditosinicio= {
        GetScreenWidth()/2 - 220,
        GetScreenHeight()/2 + 100,
        450,
        70
    };

    if(CheckCollisionPointRec(mouse,botaoCreditosinicio)){
        desenharBotao(botaoCreditosinicio, DARKBLUE);
    }

    EndDrawing();
}

void desenharGameOver(Texture2D gameOver){

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

    Vector2 mouse = GetMousePosition();

    Rectangle botaoReiniciar={
        GetScreenWidth() / 2-220,
        GetScreenHeight() / 2+100,
        450,
        70
    };

    if(CheckCollisionPointRec(mouse,botaoReiniciar)){
        desenharBotao(botaoReiniciar, YELLOW);
    }

    Rectangle botaoMenu={
        GetScreenWidth()/2 - 220,
        GetScreenHeight()/2 + 185,
        450,
        70
    };

    if(CheckCollisionPointRec(mouse,botaoMenu)){
        desenharBotao(botaoMenu, DARKBLUE);
    }

    EndDrawing();
}

void desenharGameplay(char mapa[LINHAS][COLUNAS+1],Texture2D parede,Texture2D bloco,Texture2D chao,Texture2D jogador,
    Texture2D inimigoTex,Texture2D bombaTex,Texture2D explosao,bomba bomba1,inimigo inimigos[5],int andarX,int andarY,
    int offsetX,int offsetY){

    BeginDrawing();
    ClearBackground(BLACK);

    dmapa(
        mapa,
        parede,
        bloco,
        chao,
        offsetX,
        offsetY
    );

    djogador(
        jogador,
        andarX,
        andarY,
        offsetX,
        offsetY
    );

    dbomba(
        bombaTex,
        bomba1,
        offsetX,
        offsetY
    );

    dexplosao(
        explosao,
        bomba1,
        offsetX,
        offsetY
    );

    for(int i =0;i<5;i++){
        dinimigo(
            inimigoTex,
            inimigos[i],
            offsetX,
            offsetY
        );
    }
}


void desenharTelaFinal(Texture2D telaFinal,Texture2D parede,Texture2D bloco,Texture2D chao,Texture2D jogador,Texture2D inimigoTex,
    Texture2D bombaTex,Texture2D explosao,char mapa[LINHAS][COLUNAS+1],bomba bomba1,inimigo inimigos[5],int andarX,int andarY,
    int offsetX,int offsetY,float tempoJogo,float topScore){

    desenharGameplay(mapa,parede,bloco,chao,jogador,inimigoTex,bombaTex,explosao,bomba1,inimigos, 
        andarX,andarY,offsetX,offsetY);

    DrawRectangle(
        0,
        0,
        GetScreenWidth(),
        GetScreenHeight(),
        Fade(BLACK,0.5f)
    );

    Rectangle source={
        0,
        0,
        telaFinal.width,
        telaFinal.height
    };

    Rectangle dest={
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

    DrawText(
        TextFormat("%.2f", tempoJogo),
        GetScreenWidth() / 2-160,
        680,
        35,
        WHITE
    );

    DrawText(
        TextFormat("%.2f", topScore),
        GetScreenWidth() / 2+180,
        680,
        35,
        GOLD
    );

    Vector2 mouse=GetMousePosition();

    Rectangle botaoMenu={
        GetScreenWidth() / 2-288,
        GetScreenHeight() / 2+198,
        585,
        70
    };

    if(CheckCollisionPointRec(mouse,botaoMenu)){
        desenharBotao(botaoMenu, YELLOW);
    }

    Rectangle botaoCreditos={
        GetScreenWidth()/2 -288,
        GetScreenHeight()/2+282,
        585,
        70
    };

    if(CheckCollisionPointRec(mouse, botaoCreditos)){
        desenharBotao(botaoCreditos, DARKBLUE);
    }

    EndDrawing();
}
