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

char sorteiaI(void){
    //sorteia posicao[i]
    char i;

    srand(time(NULL));
    i = 65 + rand() % 10;

    return i;
}

char sorteiaJ(void){
    //sorteia posicao[j]
    char j;

    srand(time(NULL) + 10);
    j = 48 + rand() % 10;
    return j;
}

void getPosicao(bool posicaoInicial, bool humano, char i, char j, int tamanho, int tentativa, char posicao[2]){

    if (humano == true){

        char c;
        int w = 0;

        (posicaoInicial == true) ? printf("Primeira: ") : printf("Ultima: ");

        while ( (c = getchar() ) != '\n' && c != EOF){
            posicao[w] = c;
            w++;
        }

    } else if (posicaoInicial == true && humano == false) {

        posicao[0] = sorteiaI();

        posicao[1] = sorteiaJ();

    } else if (posicaoInicial == false && humano == false){

        char i2, j2;

        switch (tentativa){

            case 0:
                i2 = i;
                j2 = j+tamanho-1;
                break;
            case 1:
                i2 = i+tamanho-1;
                j2 = j;
                break;
            case 2:
                i2 = i;
                j2 = j-tamanho+1;
                break;
            case 3:
                i2 = i-tamanho+1;
                j2 = j;
            break;
                    
            default:
                i2 = i;
                j2 = j;
                break;
        }

        posicao[0] = i2;
        posicao[1] = j2;
    
    }

}

bool verificaPosicao(bool posicaoInicial, char tabuleiro[TAMANHO][TAMANHO], bool humano,
                        int tamanho, char i, char j, char i2, char j2){

    if (posicaoInicial == true) {
        int colideIE = 0, colideID = 0, colideJE = 0, colideJD = 0;

        if (i > 74 || i < 65){
            (humano == true) ? printf("\nDigite uma posição válida!\n") : printf("");
            return false;
        } else if (j > 57 || j < 48){
            (humano == true) ? printf("\nDigite uma posição válida!\n") : printf("");
            return false;
        } else if (tabuleiro[i-64][j-47] != '~'){
            (humano == true) ? printf("\nDigite uma posição válida!\n") : printf("");
            return false;
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
                (humano == true) ? printf("\nDigite uma posição válida!\n") : printf("");
                return false;
            } else {
                return true;
            }
        }
    } else if (posicaoInicial == false) {

        if (i2 > 74 || i2 < 65){
            (humano == true) ? printf("\nDigite uma posição válida!\n") : printf("");
            return false;
        } else if (j2 > 57 || j2 < 48){
            (humano == true) ? printf("\nDigite uma posição válida!\n") : printf("");
            return false;
        } else if (i != i2 && j != j2){
            (humano == true) ? printf("\nDigite uma posição válida!\n") : printf("");
            return false;
        } else if (((((j2 - j) < 0) ? -1*(j2-j) : (j2-j)) > tamanho-1) || 
                  ((((i2 - i) < 0) ? -1*(i2-i) : (i2-i)) > tamanho-1) ){
            (humano == true) ? printf("\nDigite uma posição válida!\n") : printf("");
            return false;
        } else if ( tabuleiro[i2-64][j2-47] != '~') {
            (humano == true) ? printf("\nDigite uma posição válida!\n") : printf("");
            return false;
        } else if (i==i2){
            if ( (((j2 - j) < 0) ? -1*(j2-j) : (j2-j)) < tamanho-1){
                (humano == true) ? printf("\nDigite uma posição válida!\n") : printf("");
                return false;
            } else {
                return true;
            }
        } else if (j==j2){
            if ( (((i2 - i) < 0) ? -1*(i2-i) : (i2-i)) < tamanho-1){
                (humano == true) ? printf("\nDigite uma posição válida!\n") : printf("");
                return false;
            } else {
                return true;
            }
        } else {
            return true;
        }
    } 
    
    return false;
}

Navio setNavio(Jogador *jogador, char nome[30], char classe, int tamanho){
    
    Navio navio;
    int k;
    char i, j, i2 = '\0', j2 = '\0';
    bool posicaoValidaI = false, posicaoValidaF = false;

    navio.classe = classe;
    navio.tamanho = tamanho;

    for (k = 0; k < strlen(nome); k++){
        navio.nome[k] = nome[k];
    }
    navio.nome[k] = '\0';

    ((*jogador).humano == true) ? printf("\nDigite as posições do %s!\n", navio.nome) : printf("");

    while (posicaoValidaI == false){

        char posicao[2];

        getPosicao(true, (*jogador).humano, i, j, tamanho, 0, posicao);

        i = posicao[0];
        j = posicao[1];
        
        posicaoValidaI = verificaPosicao(true, (*jogador).tabuleiro, (*jogador).humano, tamanho, i, j, i2, j2);

    }

    while (posicaoValidaF == false){

        if ((*jogador).humano == true){

            char posicao[2];

            getPosicao(false, (*jogador).humano, i, j, tamanho, 0, posicao);

            i2 = posicao[0];
            j2 = posicao[1];

            posicaoValidaF = verificaPosicao(false, (*jogador).tabuleiro, (*jogador).humano, tamanho, i, j, i2, j2);
        
        } else {

            for (int l = 0; l < 4; l++){
                char posicao[2];

                getPosicao(false, (*jogador).humano, i, j, tamanho, l, posicao);

                posicaoValidaF = verificaPosicao(false, (*jogador).tabuleiro, (*jogador).humano, tamanho, 
                                                    i, j, posicao[0], posicao[1]);

                if (posicaoValidaF == true){
                    i2 = posicao[0];
                    j2 = posicao[1];
                    break;
                }
            }
        }

    }

    if (i == i2){
        if (j2 > j){
            for (int l = 0; l < tamanho; l++){
                (*jogador).tabuleiro[i-64][j-47+l] = navio.classe;
            }
        } else {
            for (int l = 0; l < tamanho; l++){
                (*jogador).tabuleiro[i-64][j-47-l] = navio.classe;
            }
        }
    } else {
        if (i2 > i){
            for (int l = 0; l < tamanho; l++){
                (*jogador).tabuleiro[i-64+l][j-47] = navio.classe;
            }
        } else {
            for (int l = 0; l < tamanho; l++){
                (*jogador).tabuleiro[i-64-l][j-47] = navio.classe;
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

    if ((*jogador).humano == true){ 
        imprimeTabuleiro((*jogador).tabuleiro);
    } else { 
        printf("\nAguardando computador...");
    }

    return navio;

}

bool verificaJogada(char i, char j, char jogadasRealizadas[1000][2]){

    for (int k = 0; k < 1000; k++){
        if (jogadasRealizadas[k][0] == i && jogadasRealizadas[k][1] == j){
            return false;
        }
    }

    return true;

}

void realizaDisparoIA(Jogador *computador, Jogador *jogador, int dificuldade, int rodada){

    char i, j;

    bool jogadaValida = false;

    switch (dificuldade){

        case 1:

            while (jogadaValida == false){

                i = sorteiaI();
                j = sorteiaJ();

                if (i > 74 || i < 65){
                    printf("");
                } else if (j > 57 || j < 48){
                    printf("");
                } else {
                    jogadaValida = verificaJogada(i, j, (*computador).jogadasRealizadas);
                }
            }

            for (int k = 0; k < 1000; k++){
                if ((*computador).jogadasRealizadas[k][0] == 'n' && (*computador).jogadasRealizadas[k][1] == 'n'){
                    (*computador).jogadasRealizadas[k][0] = i;
                    (*computador).jogadasRealizadas[k][1] = j;
                    break;
                }
            }

            if ((*jogador).tabuleiro[i-64][j-47] != '~'){
                (*jogador).tabuleiro[i-64][j-47] = '*';
                (*computador).pontuacao += 1;
            } else {
                (*jogador).tabuleiro[i-64][j-47] = 'X';
            }

            imprimeTabuleiro((*jogador).tabuleiro);

            break;

        case 2:

            if ( (*computador).acertouAnterior == false){

                while (jogadaValida == false){

                    i = sorteiaI();
                    j = sorteiaJ();

                    if (i > 74 || i < 65){
                        printf("");
                    } else if (j > 57 || j < 48){
                        printf("");
                    } else {
                        jogadaValida = verificaJogada(i, j, (*computador).jogadasRealizadas);
                    }
                }

                for (int k = 0; k < 1000; k++){
                    if ((*computador).jogadasRealizadas[k][0] == 'n' && (*computador).jogadasRealizadas[k][1] == 'n'){
                        (*computador).jogadasRealizadas[k][0] = i;
                        (*computador).jogadasRealizadas[k][1] = j;
                        break;
                    }
                }

                if ((*jogador).tabuleiro[i-64][j-47] != '~'){
                    (*jogador).tabuleiro[i-64][j-47] = '*';
                    (*computador).pontuacao += 1;
                    (*computador).acertouAnterior = true;
                } else {
                    (*jogador).tabuleiro[i-64][j-47] = 'X';
                }

                imprimeTabuleiro((*jogador).tabuleiro);

            } else {

                while (jogadaValida == false){

                    srand(time(NULL));
                    int sorteio = rand()%4;

                    printf("\n%d\n", sorteio);

                    switch (sorteio){
                        case 0:
                            i = (*computador).jogadasRealizadas[rodada][0]+1;
                            j = (*computador).jogadasRealizadas[rodada][1];
                            break;

                        case 1:
                            i = (*computador).jogadasRealizadas[rodada][0];
                            j = (*computador).jogadasRealizadas[rodada][1]+1;
                            break;

                        case 2:
                            i = (*computador).jogadasRealizadas[rodada][0]-1;
                            j = (*computador).jogadasRealizadas[rodada][1];
                            break;

                        case 3:
                            i = (*computador).jogadasRealizadas[rodada][0];
                            j = (*computador).jogadasRealizadas[rodada][1]-1;
                            break;
                        
                        default:
                            i = (*computador).jogadasRealizadas[rodada][0]+1;
                            j = (*computador).jogadasRealizadas[rodada][1];
                            break;
                    }

                    if (i > 74 || i < 65){
                        printf("");
                    } else if (j > 57 || j < 48){
                        printf("");
                    } else {
                        jogadaValida = verificaJogada(i, j, (*computador).jogadasRealizadas);
                    }
                }

                for (int k = 0; k < 1000; k++){
                    if ((*computador).jogadasRealizadas[k][0] == 'n' && (*computador).jogadasRealizadas[k][1] == 'n'){
                        (*computador).jogadasRealizadas[k][0] = i;
                        (*computador).jogadasRealizadas[k][1] = j;
                        break;
                    }
                }

                if ((*jogador).tabuleiro[i-64][j-47] != '~'){
                    (*jogador).tabuleiro[i-64][j-47] = '*';
                    (*computador).pontuacao += 1;
                    (*computador).acertouAnterior = true;
                } else {
                    (*jogador).tabuleiro[i-64][j-47] = 'X';
                    (*computador).acertouAnterior = false;
                }

                imprimeTabuleiro((*jogador).tabuleiro);

            }

            break;

        case 3:

                if ( (*computador).acertouAnterior == false){

                    while (jogadaValida == false){

                        i = sorteiaI();
                        j = sorteiaJ();

                        if (i > 74 || i < 65){
                            printf("");
                        } else if (j > 57 || j < 48){
                            printf("");
                        } else {
                            jogadaValida = verificaJogada(i, j, (*computador).jogadasRealizadas);
                        }
                    }

                    for (int k = 0; k < 1000; k++){
                        if ((*computador).jogadasRealizadas[k][0] == 'n' && (*computador).jogadasRealizadas[k][1] == 'n'){
                            (*computador).jogadasRealizadas[k][0] = i;
                            (*computador).jogadasRealizadas[k][1] = j;
                            break;
                        }
                    }

                    if ((*jogador).tabuleiro[i-64][j-47] != '~'){
                        (*jogador).tabuleiro[i-64][j-47] = '*';
                        (*computador).pontuacao += 1;
                        (*computador).acertouAnterior = true;
                    } else {
                        (*jogador).tabuleiro[i-64][j-47] = 'X';
                    }

                    imprimeTabuleiro((*jogador).tabuleiro);

                } else {

                    while (jogadaValida == false){

                        char iAnterior = (*computador).jogadasRealizadas[rodada][0];
                        char jAnterior = (*computador).jogadasRealizadas[rodada][1];

                        char p1 = (*jogador).tabuleiro[iAnterior-64+1][jAnterior-47];
                        char p2 = (*jogador).tabuleiro[iAnterior-64][jAnterior-47+1];
                        char p3 = (*jogador).tabuleiro[iAnterior-64-1][jAnterior-47];
                        char p4 = (*jogador).tabuleiro[iAnterior-64][jAnterior-47-1];

                        if ( p1 != '~' && p1 != '*' && p1 != 'X' && (iAnterior+1 > 64 && iAnterior+1 < 75) &&
                            verificaJogada(iAnterior+1, jAnterior, (*computador).jogadasRealizadas) == true &&
                            (jAnterior > 47 && jAnterior < 58)){
                                i = iAnterior+1;
                                j = jAnterior;
                        } else if ( p2 != '~' && p2 != '*' && p2 != 'X' && (iAnterior > 64 && iAnterior < 75) &&
                                    verificaJogada(iAnterior, jAnterior+1, (*computador).jogadasRealizadas) == true &&
                                    (jAnterior+1 > 47 && jAnterior+1 < 58)){
                                i = iAnterior;
                                j = jAnterior+1;
                        } else if ( p3 != '~' && p3 != '*' && p3 != 'X' && (iAnterior-1 > 64 && iAnterior-1 < 75) &&
                                    verificaJogada(iAnterior-1, jAnterior, (*computador).jogadasRealizadas) == true &&
                                    (jAnterior > 47 && jAnterior < 58)){
                                i = iAnterior-1;
                                j = jAnterior;
                        } else if ( p4 != '~' && p4 != '*' && p4 != 'X' && (iAnterior > 64 && iAnterior < 75) &&
                                    verificaJogada(iAnterior, jAnterior-1, (*computador).jogadasRealizadas) == true &&
                                    (jAnterior-1 > 47 && jAnterior-1 < 58)){
                                i = iAnterior;
                                j = jAnterior-1;
                        } else {
                             while (jogadaValida == false){

                                i = sorteiaI();
                                j = sorteiaJ();

                                if (i > 74 || i < 65){
                                    printf("");
                                } else if (j > 57 || j < 48){
                                    printf("");
                                } else {
                                    jogadaValida = verificaJogada(i, j, (*computador).jogadasRealizadas);
                                }
                            }
                        }
                    

                    if (i > 74 || i < 65){
                        printf("");
                    } else if (j > 57 || j < 48){
                        printf("");
                    } else {
                        jogadaValida = verificaJogada(i, j, (*computador).jogadasRealizadas);
                    }
                }

                for (int k = 0; k < 1000; k++){
                    if ((*computador).jogadasRealizadas[k][0] == 'n' && (*computador).jogadasRealizadas[k][1] == 'n'){
                        (*computador).jogadasRealizadas[k][0] = i;
                        (*computador).jogadasRealizadas[k][1] = j;
                        break;
                    }
                }

                if ((*jogador).tabuleiro[i-64][j-47] != '~'){
                    (*jogador).tabuleiro[i-64][j-47] = '*';
                    (*computador).pontuacao += 1;
                    (*computador).acertouAnterior = true;
                } else {
                    (*jogador).tabuleiro[i-64][j-47] = 'X';
                    (*computador).acertouAnterior = false;
                }

                imprimeTabuleiro((*jogador).tabuleiro);

            }
            break;
        
        default:

            while (jogadaValida == false){

                i = sorteiaI();
                j = sorteiaJ();

                if (i > 74 || i < 65){
                    printf("");
                } else if (j > 57 || j < 48){
                    printf("");
                } else {
                    jogadaValida = verificaJogada(i, j, (*computador).jogadasRealizadas);
                }
            }

            for (int k = 0; k < 1000; k++){
                if ((*computador).jogadasRealizadas[k][0] == 'n' && (*computador).jogadasRealizadas[k][1] == 'n'){
                    (*computador).jogadasRealizadas[k][0] = i;
                    (*computador).jogadasRealizadas[k][1] = j;
                    break;
                }
            }

            if ((*jogador).tabuleiro[i-64][j-47] != '~'){
                (*jogador).tabuleiro[i-64][j-47] = '*';
                (*computador).pontuacao += 1;
            } else {
                (*jogador).tabuleiro[i-64][j-47] = 'X';
            }

            imprimeTabuleiro((*jogador).tabuleiro);

            break;
    }

}

void realizaDisparo(Jogador *jogador, Jogador *jogadorAlvo){

    char i, j;

    bool jogadaValida = false;

    while (jogadaValida == false){

        char posicao[2], c;

        int w = 0;

        printf("\nDigite a posicao para disparo!\n");

        printf("Posicao: ");

        while ( (c = getchar() ) != '\n' && c != EOF){
            posicao[w] = c;
            w++;
        }

        i = posicao[0];
        j = posicao[1];

        if (i > 74 || i < 65){
            printf("\nDigite uma posição válida!\n");
        } else if (j > 57 || j < 48){
            printf("\nDigite uma posição válida!\n");
        } else {
            jogadaValida = verificaJogada(i, j, (*jogador).jogadasRealizadas);

            if (jogadaValida == false){
                printf("\nJogada ja realizada!\n");
            }
        }
    }

    for (int k = 0; k < 1000; k++){
        if ((*jogador).jogadasRealizadas[k][0] == 'n' && (*jogador).jogadasRealizadas[k][1] == 'n'){
            (*jogador).jogadasRealizadas[k][0] = i;
            (*jogador).jogadasRealizadas[k][1] = j;
            break;
        }
    }

    if ((*jogadorAlvo).tabuleiro[i-64][j-47] != '~'){
        (*jogadorAlvo).tabuleiro[i-64][j-47] = '*';
        printf("\nAcertou!\n");
        (*jogador).pontuacao += 1;
    } else {
        (*jogadorAlvo).tabuleiro[i-64][j-47] = 'X';
        printf("\nErrou!\n");
    }

    imprimeTabuleiro((*jogadorAlvo).tabuleiro);

}

int escolheModoJogo(){

    int modo = 0;

    printf("\n 1 - 1 Jogador");
    printf("\n 2 - 2 Jogadores");

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

    printf("\n 1 - Facil");
    printf("\n 2 - Normal");
    printf("\n 3 - Dificil\n");

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

    jogo.rodada = 1;
    jogo.dificuldade = escolheDificuldade();
    jogo.modoJogo = escolheModoJogo();

    return jogo;

}

int main(){

    int humano = 1;
    int computador = 0;

    Jogo jogo = setJogo();

    Jogador jogador1 = setJogador(humano);
    printf("\nBem-vindo(a)! %s %s ao Batalha Naval!\n", jogador1.titulo, jogador1.nome);

    Jogador computador1 = setJogador(computador);

    printf("\n\nAdversario %s %s", computador1.titulo, computador1.nome);

    Navio submarinoComputador = setNavio(&computador1, "Submarino", 'S', 2);

    Navio destroyerComputador = setNavio(&computador1, "Destroyer", 'D', 3);

    Navio cruzadorComputador = setNavio(&computador1, "Cruzador", 'C', 4);

    Navio portaAviaoComputador = setNavio(&computador1, "Porta-Aviões", 'P', 5);

    imprimeTabuleiro(jogador1.tabuleiro);

    Navio submarinoJogador = setNavio(&jogador1, "Submarino", 'S', 2);

    Navio destroyerJogador = setNavio(&jogador1, "Destroyer", 'D', 3);

    Navio cruzadorJogador = setNavio(&jogador1, "Cruzador", 'C', 4);

    Navio portaAviaoJogador = setNavio(&jogador1, "Porta-Aviões", 'P', 5);

    while (jogo.rodada != 50){

        realizaDisparo(&jogador1, &computador1);

        realizaDisparoIA(&computador1, &jogador1, jogo.dificuldade, jogo.rodada-2);

        jogo.rodada += 1;
    }

    return 0;
}
