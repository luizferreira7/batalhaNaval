#ifndef JOGOLOGICA_H
#define JOGOLOGICA_H

#include "comuns.h"
#include "preparaJogo.h"

char sorteiaI(void);

char sorteiaJ(void);

void getPosicao(bool posicaoInicial, bool humano, char i, char j, int tamanho, int tentativa, char posicao[2]);

bool verificaPosicao(bool posicaoInicial, char tabuleiro[TAMANHO][TAMANHO], bool humano,
                        int tamanho, char i, char j, char i2, char j2);

Navio setNavio(Jogador *jogador, char nome[30], char classe, int tamanho);


bool verificaJogada(char i, char j, char jogadasRealizadas[1000][2]);

void realizaDisparo(Jogador *jogador, Jogador *jogadorAlvo);

#endif
