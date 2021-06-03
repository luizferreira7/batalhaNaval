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

typedef struct
{
    char nome[30];
    char classe;
    int tamanho;
    char posicao[5][5];
} Navio;

void preencheTabuleiro(char tabuleiro[TAMANHO][TAMANHO]){
    // adicionando números a linha
    char numero = 47;
    for (int i = 0; i < TAMANHO; i++){
        tabuleiro[0][i] = numero;
        numero++;
    }
    // adicionando letras na coluna
    char letra = 65;
    for (int i = 1; i < TAMANHO; i++){
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

Jogador setJogador(int humano){
    Jogador jogador;

    if (humano == 1){
        int tamanho_nome;
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
    } else {
        char n[ ] = "Computador";

        int tamanho = strlen(n), i;

        for (i = 0; i < tamanho; i++){
            jogador.nome[i] = n[i];
        }
        jogador.nome[i] = '\0';

        int tamanho_nome = strlen(jogador.nome);

        for (int i = 0; i < tamanho_nome; i++){
            if (jogador.nome[i] == '\n'){
                jogador.nome[i] = '\0';
            }
        }

        sorteiaTitulo(jogador.titulo);
        jogador.pontuacao = 0;
    }

    return jogador;
}

void setNavio(char tabuleiro[TAMANHO][TAMANHO]){

    printf("\nDigite a posicao inicial do navio!\n");
    printf("Fileira: ");
    char i = getchar();

    fflush(stdin);
    fpurge(stdin);

    printf("Coluna: ");
    char j = getchar();

    tabuleiro[i-64][j-47] = 'S';

}

void acertou_ou_nao(){
    
}

void imprimeTabuleiro(char tabuleiro[TAMANHO][TAMANHO]){

    for(int i = 0; i < TAMANHO; i++){
        printf("\n");
        for(int j = 0; j < TAMANHO; j++){
            printf(" %c ", tabuleiro[i][j]);
        }
    }
}

int main(){
    char tabuleiro[TAMANHO][TAMANHO];
    preencheTabuleiro(tabuleiro);

    int humano = 1;
    int computador = 0;

    Jogador jogador1 = setJogador(humano);
    printf("\nBem-vindo(a)! %s %s ao Batalha Naval!\n", jogador1.titulo, jogador1.nome);

    Jogador computador1 = setJogador(computador);

    imprimeTabuleiro(tabuleiro);

    printf("\n\nAdversario %s %s", computador1.titulo, computador1.nome);

    setNavio(tabuleiro);

    imprimeTabuleiro(tabuleiro);

    return 0;
}
