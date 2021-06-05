#include "preparaJogo.h"

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

void preencheJogadas(char jogadasRealizadas[1000][2]){
    
    for (int i = 0; i < 1000; i++){
        jogadasRealizadas[i][0] = 'n';
        jogadasRealizadas[i][1] = 'n';
    }

}

void sorteiaTitulo(char titulo[30]){
    char almirante[ ] = "Almirante";
    char viceAlmirante[ ] = "Vice-Almirante";
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
        tamanho = strlen(viceAlmirante);
        for (i = 0; i < tamanho; i++){
        titulo[i] = viceAlmirante[i];
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
        jogador.humano = true;
        printf("Digite seu nome: ");
        fgets(jogador.nome, 30, stdin);

        for (int i = 0; i < strlen(jogador.nome); i++){
            if (jogador.nome[i] == '\n'){
                jogador.nome[i] = '\0';
            }
        }

        jogador.pontuacao = 0;
        sorteiaTitulo(jogador.titulo);
        jogador.acertouAnterior = false;
    } else {
        int i;
        char nome[ ] = "Computador";

        jogador.humano = false;

        for (i = 0; i < strlen(nome); i++){
            jogador.nome[i] = nome[i];
        }
        jogador.nome[i] = '\0';

        for (int i = 0; i < strlen(jogador.nome); i++){
            if (jogador.nome[i] == '\n'){
                jogador.nome[i] = '\0';
            }
        }

        sorteiaTitulo(jogador.titulo);
        jogador.pontuacao = 0;
        jogador.acertouAnterior = false;
    }

    preencheJogadas(jogador.jogadasRealizadas);

    preencheTabuleiro(jogador.tabuleiro);

    return jogador;
}

int escolheModoJogo(){

    int modo = 0;

    printf("\n [1] - 1 Jogador");
    printf("\n [2] - 2 Jogadores\n");

    while (modo != 1 && modo != 2){

        printf("\nEscolha o modo de Jogo: ");

        char m, c;

        while ( (c = getchar() ) != '\n' && c != EOF){
            m = c;
        }

        modo = (m - 48);

        if (modo != 1 && modo != 2){
            printf("\nModo Invalido!\n");
        }

    }

    return modo;

}

int escolheDificuldade(){

    int dificuldade = 0;

    printf("\n [1] - Facil");
    printf("\n [2] - Normal");
    printf("\n [3] - Dificil\n");

    while (dificuldade != 1 && dificuldade != 2 && dificuldade != 3){

        printf("\nEscolha a dificuldade: ");

        char dif, c;

        while ( (c = getchar() ) != '\n' && c != EOF){
            dif = c;
        }

        dificuldade = (dif - 48);

        if (dificuldade != 1 && dificuldade != 2 && dificuldade != 3){
            printf("\nDificuldade Invalida!\n");
        }

    }

    return dificuldade;

}

Jogo setJogo(){

    Jogo jogo;

    printf("\nBem-vindo ao Batalha Naval!\n");

    jogo.rodada = 1;
    jogo.dificuldade = escolheDificuldade();
    jogo.modoJogo = escolheModoJogo();

    return jogo;

}
