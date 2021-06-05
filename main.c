#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define TIMEOUT 10000000
#define TAMANHO 11

#if defined(__linux__) || defined(__APPLE__)

    #define OS 0

#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

    #define OS 1
    #include<windows.h>
    

#endif

typedef struct
{
    char tabuleiro[TAMANHO][TAMANHO];
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
    int jogadas;
} Jogador;

typedef struct
{
    char nome[30];
    char classe;
    int tamanho;
    char posicao[5][2];
} Navio;

void agua(){
    printf("\033[36m\033[44m");
}

void resetColor(){
    printf("\033[0m");
}

void disparoErro(){
    printf("\033[37m\033[44m");
}

void disparoAcerto(){
    printf("\033[31m\033[44m");
}

void navio(){
    printf("\033[33m\033[44m");
}

char COLOR_PRINT(char c, int front_color,int back_color) //cor de fundo para windows
{
 HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
 SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | back_color*16 |FOREGROUND_INTENSITY | front_color);
 printf(c);
 SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
 return c;
}

void imprimeTabuleiro(char tabuleiro[TAMANHO][TAMANHO]){

    for(int i = 0; i < TAMANHO; i++){
        printf("\n");
        for(int j = 0; j < TAMANHO; j++){
            if (OS == 0){
                if (tabuleiro[i][j] == '~'){
                    agua();
                    printf(" %c ", tabuleiro[i][j]);
                    resetColor();
                } else if (tabuleiro[i][j] == 'X'){
                    disparoErro();
                    printf(" %c ", tabuleiro[i][j]);
                    resetColor();
                } else if (tabuleiro[i][j] == '*'){
                    disparoAcerto();
                    printf(" %c ", tabuleiro[i][j]);
                    resetColor();
                } else if (j == 0){
                    resetColor();
                    printf(" %c ", tabuleiro[i][j]);
                } else if (tabuleiro[i][j] == 'S' || tabuleiro[i][j] == 'C' || 
                        tabuleiro[i][j] == 'H' || tabuleiro[i][j] == 'D' ||
                        tabuleiro[i][j] == 'P'){
                    navio();
                    printf(" %c ", tabuleiro[i][j]);
                    resetColor();
                } else {
                    resetColor();
                    printf(" %c ", tabuleiro[i][j]);
                }
            } else {
                COLOR_PRINT(tabuleiro[i][j],11,1);

            }
        }
    }
}

void imprimeTabuleiroOculto(char tabuleiro[TAMANHO][TAMANHO]){
    for(int i = 0; i < TAMANHO; i++){
        printf("\n");
        for(int j = 0; j < TAMANHO; j++){
            if(j==0){
                continue;
            }
            else(tabuleiro[i][j]=='S' || tabuleiro[i][j]=='C'||
                tabuleiro[i][j]=='D'||tabuleiro[i][j]=='P')
                {
                    printf("~");
                }
            else
            {
                printf(" %c ", tabuleiro[i][j]);
            }
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
        jogador.jogadas = 0;
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
        jogador.jogadas = 0;
    }

    preencheJogadas(jogador.jogadasRealizadas);

    preencheTabuleiro(jogador.tabuleiro);

    return jogador;
}

char sorteiaI(void){
    //sorteia posicao[i]
    char i;

    srand(time(NULL));

    int sorteio = rand() % 10;

    i = 65 + sorteio;

    return i;
}

char sorteiaJ(void){
    //sorteia posicao[j]
    char j;

    srand(time(NULL)+5);

    int sorteio = rand() % 10;

    j = 48 + sorteio;

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
            if (humano == true) { printf("\nDigite uma posição válida!\n"); }
            return false;
        } else if (j > 57 || j < 48){
            if (humano == true) { printf("\nDigite uma posição válida!\n"); }
            return false;
        } else if (tabuleiro[i-64][j-47] != '~'){
            if (humano == true) { printf("\nDigite uma posição válida!\n"); }
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
                if (humano == true) { printf("\nDigite uma posição válida!\n"); }
                return false;
            } else {
                return true;
            }
        }
    } else if (posicaoInicial == false) {

        if (i2 > 74 || i2 < 65){
            if (humano == true) { printf("\nDigite uma posição válida!\n"); }
            return false;
        } else if (j2 > 57 || j2 < 48){
            if (humano == true) { printf("\nDigite uma posição válida!\n"); }
            return false;
        } else if (i != i2 && j != j2){
            if (humano == true) { printf("\nDigite uma posição válida!\n"); }
            return false;
        } else if (((((j2 - j) < 0) ? -1*(j2-j) : (j2-j)) > tamanho-1) || 
                  ((((i2 - i) < 0) ? -1*(i2-i) : (i2-i)) > tamanho-1) ){
            if (humano == true) { printf("\nDigite uma posição válida!\n"); }
            return false;
        } else if ( tabuleiro[i2-64][j2-47] != '~') {
            if (humano == true) { printf("\nDigite uma posição válida!\n"); }
            return false;
        } else if (i==i2){
            if ( (((j2 - j) < 0) ? -1*(j2-j) : (j2-j)) < tamanho-1){
                if (humano == true) { printf("\nDigite uma posição válida!\n"); }
                return false;
            } else {
                return true;
            }
        } else if (j==j2){
            if ( (((i2 - i) < 0) ? -1*(i2-i) : (i2-i)) < tamanho-1){
                if (humano == true) { printf("\nDigite uma posição válida!\n"); }
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

Navio setNavio(Jogador *jogador, char nome[30], char classe, int tamanho, Jogo *jogo){
    
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
    printf("\n");
    if ((*jogador).humano == true) { printf("\nDigite as posições do %s!\n", navio.nome); }

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
        (*jogo).modoJogo == 1 ? imprimeTabuleiro((*jogador).tabuleiro) : imprimeTabuleiro((*jogo).tabuleiro);
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

void realizaDisparoIA(Jogador *computador, Jogador *jogador, int dificuldade, int jogada){

    char i, j;

    bool jogadaValida = false;

    unsigned long int tempo;

    switch (dificuldade){

        case 1:

            tempo = 0;

            while (jogadaValida == false){

                tempo += 1;

                if (tempo < TIMEOUT){

                    i = sorteiaI();
                    j = sorteiaJ();

                }  else {

                    int l = 1, m;
                    bool para = false;

                    while (l < TAMANHO && para == false){
                        m = 1;
                        while (m < TAMANHO && para == false){
                            if ( verificaJogada(l+64, m+47, (*computador).jogadasRealizadas) ){
                                i = l + 64;
                                j = m + 47;
                                para = true;
                            }
                            m++;
                        }
                        l++;
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
            } else {
                (*jogador).tabuleiro[i-64][j-47] = 'X';
            }

            imprimeTabuleiro((*jogador).tabuleiro);

            break;

        case 2:

            if ( (*computador).acertouAnterior == false){

                tempo = 0;

                while (jogadaValida == false){

                    tempo += 1;

                    if (tempo < TIMEOUT){

                        i = sorteiaI();
                        j = sorteiaJ();

                    }  else {

                        int l = 1, m;
                        bool para = false;

                        while (l < TAMANHO && para == false){
                            m = 1;
                            while (m < TAMANHO && para == false){
                                if ( verificaJogada(l+64, m+47, (*computador).jogadasRealizadas) ){
                                    i = l + 64;
                                    j = m + 47;
                                    para = true;
                                }
                                m++;
                            }
                            l++;
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
                }

                imprimeTabuleiro((*jogador).tabuleiro);

            } else {

                while (jogadaValida == false){

                    srand(time(NULL)+20);

                    int sorteio = rand() % 4;

                    switch (sorteio){
                        case 0:
                            i = (*computador).jogadasRealizadas[jogada][0]+1;
                            j = (*computador).jogadasRealizadas[jogada][1];
                            break;

                        case 1:
                            i = (*computador).jogadasRealizadas[jogada][0];
                            j = (*computador).jogadasRealizadas[jogada][1]+1;
                            break;

                        case 2:
                            i = (*computador).jogadasRealizadas[jogada][0]-1;
                            j = (*computador).jogadasRealizadas[jogada][1];
                            break;

                        case 3:
                            i = (*computador).jogadasRealizadas[jogada][0];
                            j = (*computador).jogadasRealizadas[jogada][1]-1;
                            break;
                        
                        default:
                            i = (*computador).jogadasRealizadas[jogada][0]+1;
                            j = (*computador).jogadasRealizadas[jogada][1];
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

                tempo = 0;

                while (jogadaValida == false){

                    tempo += 1;

                    if (tempo < TIMEOUT){

                        i = sorteiaI();
                        j = sorteiaJ();

                    }  else {

                        int l = 1, m;
                        bool para = false;

                        while (l < TAMANHO && para == false){
                            m = 1;
                            while (m < TAMANHO && para == false){
                                if ( verificaJogada(l+64, m+47, (*computador).jogadasRealizadas) ){
                                    i = l + 64;
                                    j = m + 47;
                                    para = true;
                                }
                                m++;
                            }
                            l++;
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
                }

                imprimeTabuleiro((*jogador).tabuleiro);

            } else {

                while (jogadaValida == false){

                    char iAnterior = (*computador).jogadasRealizadas[jogada][0];
                    char jAnterior = (*computador).jogadasRealizadas[jogada][1];

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

            tempo = 0;

            while (jogadaValida == false){

                if (tempo < TIMEOUT){

                    i = sorteiaI();
                    j = sorteiaJ();

                }  else {

                    int l = 1, m;
                    bool para = false;

                    while (l < TAMANHO && para == false){
                        m = 1;
                        while (m < TAMANHO && para == false){
                            if ( verificaJogada(l+64, m+47, (*computador).jogadasRealizadas) ){
                                i = l + 64;
                                j = m + 47;
                                para = true;
                            }
                            m++;
                        }
                        l++;
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
            } else {
                (*jogador).tabuleiro[i-64][j-47] = 'X';
            }

            imprimeTabuleiro((*jogador).tabuleiro);

            break;
    }

}

void realizaDisparo(Jogador *jogador, Jogador *jogadorAlvo, Jogo *jogo){

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
        (*jogador).pontuacao += 1;
        (*jogador).acertouAnterior = true;
        printf("\nAcertou!\n");
    } else {
        (*jogadorAlvo).tabuleiro[i-64][j-47] = 'X';
        (*jogador).acertouAnterior = false;
        printf("\nErrou!\n");
    }

    ((*jogo).modoJogo == 1) ? imprimeTabuleiro((*jogadorAlvo).tabuleiro) : imprimeTabuleiroOculto((*jogadorAlvo).tabuleiro);

}

int escolheModoJogo(){

    int modo = 0;

    printf("\n [1] - 1 Jogador");
    printf("\n [2] - 2 Jogadores");
    printf("\n [3] - CPU x CPU\n");

    while (modo != 1 && modo != 2 && modo != 3){

        printf("\nEscolha o modo de Jogo: ");

        char m, c;

        while ( (c = getchar() ) != '\n' && c != EOF){
            m = c;
        }

        modo = (m - 48);

        if (modo != 1 && modo != 2 && modo != 3){
            printf("\nModo Invalido!.Tente novamente.\n");
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

    printf("\n");

    return dificuldade;

}

void imprimeInventario(){

    char I_head[4][15] = {"#  Seq","Nome        ","Visual"," Tamanho  #"};
    char I_navio1[4][15] = {"#  1","Submarino   ","SS    ","    2     #"};
    char I_navio2[4][15] = {"#  2","Destroyer   ","DDD   ","    3     #"};
    char I_navio3[4][15] = {"#  3","Cruzador    ","CCCC  ","    4     #"};
    char I_navio4[4][15] = {"#  4","Porta-Aviões","PPPPP ","    5     #"};
    int i;

    printf("\n");
    printf("\n############### INVENTARIO ################\n");
    printf("#                                         #\n");

    for (i=0; i<4; i++) {
        printf("%s\t",I_head[i]);
    }

    printf("\n");

    for (i=0; i<4; i++) {    
        printf("%s\t",I_navio1[i]);
    }

    printf("\n");

    for (i=0; i<4; i++) {    
        printf("%s\t",I_navio2[i]);
    }

    printf("\n");

    for (i=0; i<4; i++) {    
        printf("%s\t",I_navio3[i]);
    }

    printf("\n");

    for (i=0; i<4; i++) {    
        printf("%s\t",I_navio4[i]);
    }

    printf("\n#                                         #");

    printf("\n###########################################\n");

}

Jogo setJogo(){

    Jogo jogo;

    printf("\nBem-vindo ao Batalha Naval!\n");

    jogo.rodada = 1;
    jogo.modoJogo = escolheModoJogo();

    preencheTabuleiro(jogo.tabuleiro);

    if(jogo.modoJogo != 2){
        jogo.dificuldade = escolheDificuldade();
    }

    return jogo;

}

int main(){

    int humano = 1;
    int comp = 0;
  
    Jogo jogo = setJogo();

    if (jogo.modoJogo == 1){

        Jogador jogador1 = setJogador(humano);

        printf("\n\nJogador %s %s\n", jogador1.titulo, jogador1.nome);
        
        Jogador computador = setJogador(comp);

        printf("\n\nAdversario %s %s\n", computador.titulo, computador.nome);

        Navio submarinoComputador = setNavio(&computador, "Submarino", 'S', 2, &jogo);

        Navio destroyerComputador = setNavio(&computador, "Destroyer", 'D', 3, &jogo);

        Navio cruzadorComputador = setNavio(&computador, "Cruzador", 'C', 4, &jogo);

        Navio portaAviaoComputador = setNavio(&computador, "Porta-Aviões", 'P', 5, &jogo);

        imprimeInventario();

        imprimeTabuleiro(jogador1.tabuleiro);

        Navio submarinoJogador = setNavio(&jogador1, "Submarino", 'S', 2, &jogo);

        imprimeInventario();

        Navio destroyerJogador = setNavio(&jogador1, "Destroyer", 'D', 3, &jogo);

        imprimeInventario();

        Navio cruzadorJogador = setNavio(&jogador1, "Cruzador", 'C', 4, &jogo);

        imprimeInventario();

        Navio portaAviaoJogador = setNavio(&jogador1, "Porta-Aviões", 'P', 5, &jogo);

        while (jogo.rodada != 50){

            jogador1.jogadas += 1;
            realizaDisparo(&jogador1, &computador, &jogo);

            while (jogador1.acertouAnterior == true){
                jogador1.jogadas += 1;
                realizaDisparo(&jogador1, &computador, &jogo);
            }

            printf("\n");

            computador.jogadas += 1;
                realizaDisparoIA(&computador, &jogador1, jogo.dificuldade, computador.jogadas-2);

            while (computador.acertouAnterior == true){
                computador.jogadas += 1;
                realizaDisparoIA(&computador, &jogador1, jogo.dificuldade, computador.jogadas-2);
            }

            jogo.rodada += 1;
        }

    } else if (jogo.modoJogo == 3) {

        Jogador computador = setJogador(comp);

        printf("\n\nAdversario %s %s\n", computador.titulo, computador.nome);

        Navio submarinoComputador = setNavio(&computador, "Submarino", 'S', 2, &jogo);

        Navio destroyerComputador = setNavio(&computador, "Destroyer", 'D', 3, &jogo);

        Navio cruzadorComputador = setNavio(&computador, "Cruzador", 'C', 4, &jogo);

        Navio portaAviaoComputador = setNavio(&computador, "Porta-Aviões", 'P', 5, &jogo);

        Jogador computador2 = setJogador(comp);

        printf("\n\nAdversario %s %s\n", computador2.titulo, computador2.nome);

        Navio submarinoComputador2 = setNavio(&computador2, "Submarino", 'S', 2, &jogo);

        Navio destroyerComputador2 = setNavio(&computador2, "Destroyer", 'D', 3, &jogo);

        Navio cruzadorComputador2 = setNavio(&computador2, "Cruzador", 'C', 4, &jogo);

        Navio portaAviaoComputador2 = setNavio(&computador2, "Porta-Aviões", 'P', 5, &jogo);

        while (jogo.rodada != 50){

            computador.jogadas += 1;
                realizaDisparoIA(&computador, &computador2, jogo.dificuldade, computador.jogadas-2);

            while (computador.acertouAnterior == true){
                computador.jogadas += 1;
                realizaDisparoIA(&computador, &computador2, jogo.dificuldade, computador.jogadas-2);
            }

            printf("\n");

            computador2.jogadas += 1;
                realizaDisparoIA(&computador2, &computador, jogo.dificuldade, computador2.jogadas-2);

            while (computador2.acertouAnterior == true){
                computador2.jogadas += 1;
                realizaDisparoIA(&computador2, &computador, jogo.dificuldade, computador2.jogadas-2);
            }

            jogo.rodada += 1;
        }

    } else {

        Jogador jogador1 = setJogador(humano);

        printf("\n\nJogador %s %s\n", jogador1.titulo, jogador1.nome);

        imprimeInventario();

        imprimeTabuleiro(jogo.tabuleiro);
        
        Navio submarinoJogador = setNavio(&jogador1, "Submarino", 'S', 2, &jogo);

        Navio destroyerJogador = setNavio(&jogador1, "Destroyer", 'D', 3, &jogo);

        Navio cruzadorJogador = setNavio(&jogador1, "Cruzador", 'C', 4, &jogo);

        Navio portaAviaoJogador = setNavio(&jogador1, "Porta-Aviões", 'P', 5, &jogo);

        printf("\nAgora, ao oponente!\n");

        Jogador jogador2 = setJogador(humano);

        printf("\n\nAdversario %s %s\n", jogador2.titulo, jogador2.nome);

        imprimeInventario();

        imprimeTabuleiro(jogo.tabuleiro);

        Navio submarinoJogador2 = setNavio(&jogador2, "Submarino", 'S', 2, &jogo);

        Navio destroyerJogador2 = setNavio(&jogador2, "Destroyer", 'D', 3, &jogo);

        Navio cruzadorJogador2= setNavio(&jogador2, "Cruzador", 'C', 4, &jogo);

        Navio portaAviaoJogador2 = setNavio(&jogador2, "Porta-Aviões", 'P', 5, &jogo);

        while (jogo.rodada != 50){

            jogador1.jogadas += 1;
                realizaDisparo(&jogador1, &jogador2, &jogo);

            while (jogador1.acertouAnterior == true){
                jogador1.jogadas += 1;
                realizaDisparo(&jogador1, &jogador2, &jogo);
            }

            printf("\n");

            jogador2.jogadas += 1;
                realizaDisparo(&jogador2, &jogador1, &jogo);

            while (jogador2.acertouAnterior == true){
                jogador2.jogadas += 1;
                realizaDisparo(&jogador2, &jogador1, &jogo);
            }

            jogo.rodada += 1;
        }

    }

    return 0;
}
