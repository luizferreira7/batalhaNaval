#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
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
    char posicao[5][2];
} Navio;

void imprimeTabuleiro(char tabuleiro[TAMANHO][TAMANHO]){

    for(int i = 0; i < TAMANHO; i++){
        printf("\n");
        for(int j = 0; j < TAMANHO; j++){
            printf(" %c ", tabuleiro[i][j]);
        }
    }
}

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

Navio setNavio(char tabuleiro[TAMANHO][TAMANHO], char nome[30],
        char classe, int tamanho){
    Navio navio;
    int k;
    char i, j, i2, j2;
    bool posicaoValidaI = false, posicaoValidaF = false;

    navio.classe = classe;
    navio.tamanho = tamanho;

    for (k = 0; k < strlen(nome); k++){
        navio.nome[k] = nome[k];
    }
    navio.nome[k] = '\0';

    printf("\nDigite as posições do %s!\n", navio.nome);

    while (posicaoValidaI == false){
        int colideIE = 0, colideID = 0, colideJE = 0, colideJD = 0, w = 0;

        char posicaoI[2], c;

        printf("Primeira: ");
        
        while ( (c = getchar() ) != '\n' && c != EOF){
            posicaoI[w] = c;
            w++;
        }

        i = posicaoI[0];
        j = posicaoI[1];

        if (i > 74 || i < 65){
            printf("\nDigite uma posição válida!\n");
        } else if (j > 57 || j < 48){
            printf("\nDigite uma posição válida!\n");
        } else if (tabuleiro[i-64][j-47] != '~'){
            printf("\nDigite uma posição válida!\n");
        } else {
            for (int a = 0; a < tamanho; a++){
                if (i-64+a < TAMANHO){
                    if (tabuleiro[i-64+a][j-47] != '~'){
                        colideJD += 1;
                    }
                } else {
                    colideJD += 1;
                }
                if (i-64-a > 0){
                    if (tabuleiro[i-64-a][j-47] != '~'){
                        colideJE += 1;
                    }
                } else {
                    colideJE += 1;
                }
            }
            for (int b = 0; b < tamanho; b++){
                if (j-47+b < TAMANHO){
                    if (tabuleiro[i-64][j-47+b] != '~'){
                        colideID += 1;
                    }
                } else {
                    colideID += 1;
                }
                if (j-47-b > 0){
                    if (tabuleiro[i-64][j-47-b] != '~'){
                        colideIE += 1;
                    }
                } else {
                    colideIE += 1;
                }
            }
            if (colideIE != 0 && colideJD != 0 && colideID != 0 && colideJE != 0){
                printf("\nDigite uma posição válida!\n");
            } else {
                posicaoValidaI = true;
            }
        }

        fflush(stdin);
    }

    while (posicaoValidaF == false){
        char posicaoF[2], c;

        int w = 0;

        printf("Ultima: ");

        while ( (c = getchar() ) != '\n' && c != EOF){
            posicaoF[w] = c;
            w++;
        }

        i2 = posicaoF[0];
        j2 = posicaoF[1];

        if (i2 > 74 || i2 < 65){
            printf("\nDigite uma posição válida!\n");
        } else if (j2 > 57 || j2 < 48){
            printf("\nDigite uma posição válida!\n");
        } else if (i != i2 && j != j2){
            printf("\nDigite uma posição válida!\n");
        } else if (((((j2 - j) < 0) ? -1*(j2-j) : (j2-j)) > tamanho-1) || 
                  ((((i2 - i) < 0) ? -1*(i2-i) : (i2-i)) > tamanho-1) ){
            printf("\nDigite uma posição válida!\n");
        } else if (i==i2){
            if ( (((j2 - j) < 0) ? -1*(j2-j) : (j2-j)) < tamanho-1){
                printf("\nDigite uma posição válida!\n");
            } else {
                posicaoValidaF = true;
            }
        } else if (j==j2){
            if ( (((i2 - i) < 0) ? -1*(i2-i) : (i2-i)) < tamanho-1){
                printf("\nDigite uma posição válida!\n");
            } else {
                posicaoValidaF = true;
            }
        } else {
            posicaoValidaF = true;
        }

        fflush(stdin);
    }

    if (i == i2){
        if (j2 > j){
            for (int l = 0; l < tamanho; l++){
                tabuleiro[i-64][j-47+l] = navio.classe;
            }
        } else {
            for (int l = 0; l < tamanho; l++){
                tabuleiro[i-64][j-47-l] = navio.classe;
            }
        }
    } else {
        if (i2 > i){
            for (int l = 0; l < tamanho; l++){
                tabuleiro[i-64+l][j-47] = navio.classe;
            }
        } else {
            for (int l = 0; l < tamanho; l++){
                tabuleiro[i-64-l][j-47] = navio.classe;
            }
        }
    }

    for (int l = 0; l < tamanho; l++){
        if (i == i2){
            navio.posicao[l][0] = i;
            navio.posicao[l][1] = j + l;
        } else {
            navio.posicao[l][0] = i + l;
            navio.posicao[l][1] = j;
        }
    }

    imprimeTabuleiro(tabuleiro);

    return navio;

}

void acertou_ou_nao(){
    
}

bool verificaJogada(char i, char j){

    char jogadasRealizadas[TAMANHO][TAMANHO];

    return true;

}

int main(){
    char tabuleiroJogador[TAMANHO][TAMANHO];
    char tabuleiroInimigo[TAMANHO][TAMANHO];

    preencheTabuleiro(tabuleiroJogador);
    preencheTabuleiro(tabuleiroInimigo);

    char jogadasRealizadasJ1[TAMANHO][TAMANHO];

    int humano = 1;
    int computador = 0;

    Jogador jogador1 = setJogador(humano);
    printf("\nBem-vindo(a)! %s %s ao Batalha Naval!\n", jogador1.titulo, jogador1.nome);

    Jogador computador1 = setJogador(computador);

    imprimeTabuleiro(tabuleiroJogador);

    printf("\n\nAdversario %s %s", computador1.titulo, computador1.nome);

    Navio submarinoJogador = setNavio(tabuleiroJogador, "Submarino", 'S', 2);

    Navio destroyerJogador = setNavio(tabuleiroJogador, "Destroyer", 'D', 3);

    Navio cruzadorJogador = setNavio(tabuleiroJogador, "Cruzador", 'C', 3);

    Navio portaAvioJogador = setNavio(tabuleiroJogador, "Porta-Avião", 'P', 4);

    imprimeTabuleiro(tabuleiroJogador);

    return 0;
}
