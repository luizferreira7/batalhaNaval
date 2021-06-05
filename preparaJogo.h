#ifndef PREPARAJOGO_H
#define PREPARAJOGO_H

#include "struct.h"

void imprimeTabuleiro(char tabuleiro[TAMANHO][TAMANHO]);

void preencheTabuleiro(char tabuleiro[TAMANHO][TAMANHO]);

void preencheJogadas(char jogadasRealizadas[1000][2]);

void sorteiaTitulo(char titulo[30]);

Jogador setJogador(int humano);

int escolheModoJogo();

int escolheDificuldade();

Jogo setJogo();

#endif
