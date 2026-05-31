#include <stdlib.h>
#include <stdio.h>

#include "bomba.h"
#include "render.h"
#include "inimigo.h"
#include "gameplay.h"
#include "score.h"

int pixel = 64;


int main(){

    char mapa[LINHAS][COLUNAS+1]={
        "#####################",
        "#   *   *     ***   #",
        "#  *    *  *  *     #",
        "#    * *  *    *    #",
        "#     **     *   *  #",
        "#   * *   *  *  **  #",
        "#    *  *   *   *   #",
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
        "#  * *  *   *   *   #",
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
        "# ** *  *  **   **  #",
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

    score *listaScores = NULL;
    carregarScores(&listaScores);

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
    Texture2D vidaCheia = LoadTexture("assets/cheio.png");
    Texture2D vidaVazia = LoadTexture("assets/vazio.png");

    SetTargetFPS(60);
    
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
                GetScreenWidth()/2 - 150,
                GetScreenHeight()/2 + 10,
                310,
                55
            };

            if(CheckCollisionPointRec(mouse, botaojogar) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                resetarJogo(mapa,&bomba1,inimigos,&vidas,&fase,&faseatual,&andarX,&andarY,&tempoJogo);

                estadoJogo = 1;
            }

            Rectangle botaoSair = {
                GetScreenWidth()/2 - 150,
                GetScreenHeight()/2 + 140,
                310,
                55
            };

            if(CheckCollisionPointRec(mouse, botaoSair) &&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                CloseWindow();
            }

            Rectangle botaoCreditosinicio={
                GetScreenWidth()/2 - 150,
                GetScreenHeight()/2 + 75,
                310,
                55
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

                inserirScoreOrdenado(&listaScores, tempoJogo);
                salvarScores(listaScores);

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

            float topScore = 0;

            if(listaScores != NULL){
                topScore = listaScores->tempo;
            }
            desenharTelaFinal(telaFinal,parede,bloco,chao,jogador,inimigo,bombaTex,explosao,mapa,bomba1,inimigos,andarX,andarY,
                offsetX,offsetY,tempoJogo,topScore);

            Vector2 mouse = GetMousePosition();

            Rectangle botaoMenu={
                GetScreenWidth()/2 - 195,
                GetScreenHeight()/2 +155,
                400,
                50
            };

            Rectangle botaoCreditos = {
                GetScreenWidth()/2 - 195,
                GetScreenHeight()/2 +215,
                400,
                50
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
                        GetScreenWidth()/2 - 150,
                        GetScreenHeight()/2 + 75,
                        310,
                        55
                    };

                    Rectangle botaoMenu = {
                        GetScreenWidth()/2 - 150,
                        GetScreenHeight()/2 + 140,
                        310,
                        55
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

        desenharVidas(vidaCheia, vidaVazia, vidas);
            
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

    liberarScores(listaScores);

    return 0;
    }
