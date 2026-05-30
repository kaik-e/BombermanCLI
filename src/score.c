#include <stdio.h>
#include <stdlib.h>
#include "score.h"

void inserirScoreOrdenado(score **head,float tempo){
    score *novo=malloc(sizeof(score));

    novo->tempo = tempo;
    novo->prox = NULL;

    if(*head == NULL||tempo < (*head)->tempo){
        novo->prox=*head;
        *head = novo;
        return;
    }

    score *atual = *head;

    while(atual->prox != NULL &&atual->prox->tempo < tempo){
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
}

void carregarScores(score **head){
    FILE *arquivo =fopen("scores.txt","r");

    if(arquivo == NULL){
        return;
    }

    float tempo;

    while(fscanf(arquivo, "%f", &tempo) == 1){
        inserirScoreOrdenado(head, tempo);
    }

    fclose(arquivo);
}

void salvarScores(score *head){
    FILE *arquivo = fopen("scores.txt", "w");

    if(arquivo == NULL){
        return;
    }

    score *atual = head;

    while(atual != NULL){
        fprintf(arquivo, "%.2f\n", atual->tempo);
        atual = atual->prox;
    }

    fclose(arquivo);
}

void liberarScores(score *head){
    while(head != NULL){
        score *temp = head;
        head = head->prox;

        free(temp);
    }
}