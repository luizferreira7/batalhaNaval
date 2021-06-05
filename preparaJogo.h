#ifndef PREPARAJOGO_H
#define PREPARAJOGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define TAMANHO 11

typedef struct
{
    int rodada;
    int dificuldade;
    int modoJogo;
} Jogo;


typedef struct
{
    bool humano;
    char nome[30];
    char titulo[20];
    int pontuacao;
    char jogadasRealizadas[1000][2];
    char tabuleiro[TAMANHO][TAMANHO];
    bool acertouAnterior;
} Jogador;

typedef struct
{
    char nome[30];
    char classe;
    int tamanho;
    char posicao[5][2];
} Navio;

void imprimeTabuleiro(char tabuleiro[TAMANHO][TAMANHO]);

void preencheTabuleiro(char tabuleiro[TAMANHO][TAMANHO]);

void preencheJogadas(char jogadasRealizadas[1000][2]);

void sorteiaTitulo(char titulo[30]);

Jogador setJogador(int humano);

int escolheModoJogo();

int escolheDificuldade();

Jogo setJogo();

#endif
