#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAMANHO 11

typedef struct
{
    char nome[30];
    char titulo[20];
    int pontuacao;
} Jogador;

void preencheTabuleiro(char tabuleiro[TAMANHO][TAMANHO]){
    // adicionando números a linha
    char numero = 48;
    for (int i = 0; i < TAMANHO; i++){
        if (i == 10)
        {
            tabuleiro[0][i] = 49;
            break;
        }
        
        tabuleiro[0][i] = numero;
        numero++;
    }
    // adicionando letras na coluna
    char letra = 64;
    for (int i = 0; i < TAMANHO; i++){
        tabuleiro[i][0] = letra;
        letra++;
    }
    // acidionando água
    for (int i = 1; i < TAMANHO; i++){
        for (int j = 1; j < TAMANHO; j++){
            tabuleiro[i][j] = '~';
        } 
    }
}

void sorteiaTitulo(char titulo[30]){
    char almirante[ ] = "Almirante";
    char vice_almirante[ ] = "Vice-Almirante";
    char capitao[ ] = "Cap.";
    char tenente[ ] = "Tenente";
    int sorteio, tamanho, i;

    srand(time(NULL));

    sorteio = rand() % 4;

    if (sorteio == 0){
        tamanho = strlen(almirante);
        for (i = 0; i < tamanho; i++){
        titulo[i] = almirante[i];
        }
        titulo[i] = '\0';
    } else if (sorteio == 1){
        tamanho = strlen(vice_almirante);
        for (i = 0; i < tamanho; i++){
        titulo[i] = vice_almirante[i];
        }
        titulo[i] = '\0';
    } else if (sorteio == 2){
        tamanho = strlen(capitao);
        for (i = 0; i < tamanho; i++){
        titulo[i] = capitao[i];
        }
        titulo[i] = '\0';
    } else if (sorteio == 3){
        tamanho = strlen(tenente);
        for (i = 0; i < tamanho; i++){
        titulo[i] = tenente[i];
        }
        titulo[i] = '\0';
    }
}

Jogador setJogador(){
    int tamanho_nome;
    Jogador jogador;
    printf("Digite seu nome: ");
    fgets(jogador.nome, 30, stdin);

    tamanho_nome = strlen(jogador.nome);

    for (int i = 0; i < tamanho_nome; i++){
        if (jogador.nome[i] == '\n'){
            jogador.nome[i] = '\0';
        }
    }

    jogador.pontuacao = 0;
    sorteiaTitulo(jogador.titulo);

    return jogador;
}

int main(){
    char tabuleiro[TAMANHO][TAMANHO];
    preencheTabuleiro(tabuleiro);

    Jogador jogador1 = setJogador();
    printf("\nBem-vindo(a)! %s %s ao Batalha Naval!\n", jogador1.titulo, jogador1.nome);

    for(int i = 0; i < TAMANHO; i++){
        for(int j = 0; j < TAMANHO; j++){
            printf(" %c ", tabuleiro[i][j]);
            if (i == 0 && j == 10){
                printf("%d",0);
            }
        }
        printf("\n");
    }

    return 0;
}
