#ifndef SCORE_H
#define SCORE_H

typedef struct score{
    float tempo;
    struct score *prox;
} score;

void inserirScoreOrdenado(score **head, float tempo);

void carregarScores(score **head);

void salvarScores(score *head);

void liberarScores(score *head);

#endif