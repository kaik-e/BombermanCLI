#ifndef RENDER_H
#define RENDER_H

#include "raylib.h"

#define LINHAS 13
#define COLUNAS 21

extern int pixel;

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
} inimigo;

void dmapa(char mapa[LINHAS][COLUNAS+1],Texture2D parede,Texture2D bloco,Texture2D chao,int offsetX,int offsetY);

void djogador(Texture2D jogador,int x,int y,int offsetX,int offsetY);

void dbomba( Texture2D bombaTex,bomba bomba1,int offsetX,int offsetY);

void desenharFrameExplosao(Texture2D explosao,int frame, int x,int y,int offsetX,int offsetY);

void dexplosao(Texture2D explosao,bomba bomba1,int offsetX,int offsetY);

void dinimigo(Texture2D inimigo,inimigo inimigo1,int offsetX,int offsetY);

void desenharBotao(Rectangle botao,Color cor
);

void desenharCreditos();

void desenharMenu(Texture2D menu);

void desenharGameOver(Texture2D gameOver);

void desenharGameplay(
    char mapa[LINHAS][COLUNAS+1],
    Texture2D parede,
    Texture2D bloco,
    Texture2D chao,
    Texture2D jogador,
    Texture2D inimigoTex,
    Texture2D bombaTex,
    Texture2D explosao,
    bomba bomba1,
    inimigo inimigos[5],
    int andarX,
    int andarY,
    int offsetX,
    int offsetY
);

void desenharTelaFinal(
    Texture2D telaFinal,
    Texture2D parede,
    Texture2D bloco,
    Texture2D chao,
    Texture2D jogador,
    Texture2D inimigoTex,
    Texture2D bombaTex,
    Texture2D explosao,
    char mapa[LINHAS][COLUNAS+1],
    bomba bomba1,
    inimigo inimigos[5],
    int andarX,
    int andarY,
    int offsetX,
    int offsetY,
    float tempoJogo,
    float topScore
);

#endif