#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define TIMEOUT 10000000
#define TAMANHO 11
#define PONTUACAO_MAX 14

#if defined(__linux__) || defined(__APPLE__)

    #define OS 0

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

    void imprimeTabuleiro(char tabuleiro[TAMANHO][TAMANHO]){

        for(int i = 0; i < TAMANHO; i++){
            printf("\n");
            for(int j = 0; j < TAMANHO; j++){
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
            }
        }
    }

    void imprimeTabuleiroOculto(char tabuleiro[TAMANHO][TAMANHO]){
        for(int i = 0; i < TAMANHO; i++){
            printf("\n");
            for(int j = 0; j < TAMANHO; j++){
                if(j==0){
                    printf(" %c ", tabuleiro[i][j]);
                } else if (tabuleiro[i][j]=='S' || tabuleiro[i][j]=='C'||
                    tabuleiro[i][j]=='D'||tabuleiro[i][j]=='P'){
                    agua();
                    printf(" ~ ");
                    resetColor();
                } else if(tabuleiro[i][j]=='~'){
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
                } else {
                    printf(" %c ", tabuleiro[i][j]);
                }
            }
        }
    }

#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

    #define OS 1
    #include<windows.h>

    char COLOR_PRINT(char c, int front_color,int back_color) //cor de fundo para windows
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, BACKGROUND_INTENSITY | back_color*16 |FOREGROUND_INTENSITY | front_color);
        printf(" %c ", c);
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
        return c;
    }

    void imprimeTabuleiro(char tabuleiro[TAMANHO][TAMANHO]){

        for(int i = 0; i < TAMANHO; i++){
            printf("\n");
            for(int j = 0; j < TAMANHO; j++){
                if(tabuleiro[i][j]=='~'){
                    COLOR_PRINT(tabuleiro[i][j],11,1);
                } else if(tabuleiro[i][j] == 'X'){
                    COLOR_PRINT(tabuleiro[i][j],15,1);
                } else if(tabuleiro[i][j] == '*'){
                    COLOR_PRINT(tabuleiro[i][j],4,1);
                } else if (j == 0){
                    printf(" %c ", tabuleiro[i][j]);
                } else if (tabuleiro[i][j] == 'S' || tabuleiro[i][j] == 'C' || 
                        tabuleiro[i][j] == 'H' || tabuleiro[i][j] == 'D' || 
                        tabuleiro[i][j] == 'P'){
                    COLOR_PRINT(tabuleiro[i][j],6,1);        
                } else {
                    printf(" %c ", tabuleiro[i][j]);
                }

            }
        }
    }


    void imprimeTabuleiroOculto(char tabuleiro[TAMANHO][TAMANHO]){
        for(int i = 0; i < TAMANHO; i++){
            printf("\n");
            for(int j = 0; j < TAMANHO; j++){
                if(j==0){
                    printf(" %c ", tabuleiro[i][j]);
                } else if (tabuleiro[i][j]=='S' || tabuleiro[i][j]=='C'||
                    tabuleiro[i][j]=='D'||tabuleiro[i][j]=='P'){
                    COLOR_PRINT('~',11,1);
                } else if(tabuleiro[i][j]=='~'){
                    COLOR_PRINT('~',11,1);
                } else if(tabuleiro[i][j] == 'X'){
                    COLOR_PRINT(tabuleiro[i][j],15,1);
                } else if(tabuleiro[i][j] == '*'){
                    COLOR_PRINT(tabuleiro[i][j],4,1);
                } else {
                    printf(" %c ", tabuleiro[i][j]);
                }
            }
        }
    }
    

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


void imprimeInventario(){

    char I_head[4][15] = {"#  Seq","Nome        ","Visual"," Tamanho  #"};
    char I_navio1[4][15] = {"#  1","Submarino   ","SS    ","    2     #"};
    char I_navio2[4][15] = {"#  2","Destroyer   ","DDD   ","    3     #"};
    char I_navio3[4][15] = {"#  3","Cruzador    ","CCCC  ","    4     #"};
    char I_navio4[4][15] = {"#  4","Porta-Avioes","PPPPP ","    5     #"};
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

void preencheTabuleiro(char tabuleiro[TAMANHO][TAMANHO]){
    // adicionando n??meros a linha
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
    // acidionando agua
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

void sorteiaTitulo(char titulo[30], int n){
    char almirante[ ] = "Almirante";
    char viceAlmirante[ ] = "Vice-Almirante";
    char capitao[ ] = "Cap.";
    char tenente[ ] = "Tenente";
    int sorteio, tamanho, i;

    srand(time(NULL)+n);

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

Jogador setJogador(int humano, char nome[20]){
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
        sorteiaTitulo(jogador.titulo, strlen(jogador.nome));
        jogador.acertouAnterior = false;
        jogador.jogadas = 0;
    } else {
        int i;

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

        sorteiaTitulo(jogador.titulo, strlen(jogador.nome));
        jogador.pontuacao = 0;
        jogador.acertouAnterior = false;
        jogador.jogadas = 0;
    }

    preencheJogadas(jogador.jogadasRealizadas);

    preencheTabuleiro(jogador.tabuleiro);

    return jogador;
}

void recuperaNomeNavio(char classe, char nome[20]){

    if (classe == 'S'){
        int i;
        char navio[ ] = {"Submarino"};
        for(i = 0; i < strlen(navio); i++){
            nome[i] = navio[i];
        }
        nome[i] = '\0';
    } else if (classe == 'D'){
        int i;
        char navio[ ] = {"Destroyer"};
        for(i = 0; i < strlen(navio); i++){
            nome[i] = navio[i];
        }
        nome[i] = '\0';
    } else if (classe == 'C'){
        int i;
        char navio[ ] = {"Cruzador"};
        for(i = 0; i < strlen(navio); i++){
            nome[i] = navio[i];
        }
        nome[i] = '\0';
    } else if (classe == 'P'){
        int i;
        char navio[ ] = {"Porta-Avioes"};
        for(i = 0; i < strlen(navio); i++){
            nome[i] = navio[i];
        }
        nome[i] = '\0';
    }

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

void getPosicao(bool posicaoInicial, char i, char j, int tamanho, int tentativa, char posicao[2], bool automatico){

    if (automatico == false){

        char c;
        int w = 0;

        (posicaoInicial == true) ? printf("Primeira: ") : printf("Ultima: ");

        while ( (c = getchar() ) != '\n' && c != EOF){
            posicao[w] = c;
            w++;
        }

    } else if (posicaoInicial == true && automatico == true) {

        posicao[0] = sorteiaI();

        posicao[1] = sorteiaJ();

    } else if (posicaoInicial == false && automatico == true){

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

bool verificaPosicao(bool posicaoInicial, char tabuleiro[TAMANHO][TAMANHO], bool automatico,
                        int tamanho, char i, char j, char i2, char j2){

    if (posicaoInicial == true) {
        int colideIE = 0, colideID = 0, colideJE = 0, colideJD = 0;

        if (i > 74 || i < 65){
            if (automatico == false) { printf("\nDigite uma posicao valida!\n"); }
            return false;
        } else if (j > 57 || j < 48){
            if (automatico == false) { printf("\nDigite uma posicao valida!\n"); }
            return false;
        } else if (tabuleiro[i-64][j-47] != '~'){
            if (automatico == false) { printf("\nDigite uma posicao valida!\n"); }
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
                if (automatico == false) { printf("\nDigite uma posicao valida!\n"); }
                return false;
            } else {
                return true;
            }
        }
    } else if (posicaoInicial == false) {

        if (i2 > 74 || i2 < 65){
            if (automatico == false) { printf("\nDigite uma posicao valida!\n"); }
            return false;
        } else if (j2 > 57 || j2 < 48){
            if (automatico == false) { printf("\nDigite uma posicao valida!\n"); }
            return false;
        } else if (i != i2 && j != j2){
            if (automatico == false) { printf("\nDigite uma posicao valida!\n"); }
            return false;
        } else if (((((j2 - j) < 0) ? -1*(j2-j) : (j2-j)) > tamanho-1) || 
                  ((((i2 - i) < 0) ? -1*(i2-i) : (i2-i)) > tamanho-1) ){
            if (automatico == false) { printf("\nDigite uma posicao valida!\n"); }
            return false;
        } else if ( tabuleiro[i2-64][j2-47] != '~') {
            if (automatico == false) { printf("\nDigite uma posicao valida!\n"); }
            return false;
        } else if (i==i2){

            for (int m = j-47+1; m < j2-47; m++){
                if (tabuleiro[i-64][m] != '~'){
                    if (automatico == false) { printf("\nDigite uma posicao valida!\n"); }
                    return false;
                }
            }

            for (int m = j2-47+1; m < j-47; m++){
                if (tabuleiro[i-64][m] != '~'){
                    if (automatico == false) { printf("\nDigite uma posicao valida!\n"); }
                    return false;
                }
            }

            if ( (((j2 - j) < 0) ? -1*(j2-j) : (j2-j)) < tamanho-1){
                if (automatico == false) { printf("\nDigite uma posicao valida!\n"); }
                return false;
            } else {
                return true;
            }
        } else if (j==j2){

            for (int m = i-64+1; m < i2-64; m++){
                if (tabuleiro[m][j-47] != '~'){
                    if (automatico == false) { printf("\nDigite uma posicao valida!\n"); }
                    return false;
                }
            }

            for (int m = i2-64+1; m < i-64; m++){
                if (tabuleiro[m][j-47] != '~'){
                    if (automatico == false) { printf("\nDigite uma posicao valida!\n"); }
                    return false;
                }
            }

            if ( (((i2 - i) < 0) ? -1*(i2-i) : (i2-i)) < tamanho-1){
                if (automatico == false) { printf("\nDigite uma posicao valida!\n"); }
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

Navio setNavio(char nome[30], char classe, int tamanho){
    
    Navio navio;
    int k;

    navio.classe = classe;
    navio.tamanho = tamanho;

    for (k = 0; k < strlen(nome); k++){
        navio.nome[k] = nome[k];
    }
    navio.nome[k] = '\0';

    return navio;

}

void setTabuleiro(Jogador *jogador, Navio *navio, Jogo *jogo, bool automatico){
    
    char i, j, i2 = '\0', j2 = '\0';
    bool posicaoValidaI = false, posicaoValidaF = false;

    printf("\n");
    if ((*jogador).humano == true && automatico == false ) { printf("\nDigite as posicoes do %s!\n", (*navio).nome); }

    while (posicaoValidaI == false){

        char posicao[2];

        getPosicao(true, i, j, (*navio).tamanho, 0, posicao, automatico);

        i = posicao[0];
        j = posicao[1];
        
        posicaoValidaI = verificaPosicao(true, (*jogador).tabuleiro, automatico, (*navio).tamanho, i, j, i2, j2);

    }

    while (posicaoValidaF == false){

        if ((*jogador).humano == true && automatico == false){

            char posicao[2];

            getPosicao(false, i, j, (*navio).tamanho, 0, posicao, automatico);

            i2 = posicao[0];
            j2 = posicao[1];

            posicaoValidaF = verificaPosicao(false, (*jogador).tabuleiro, automatico, (*navio).tamanho, 
                                                i, j, i2, j2);
        
        } else {

            for (int l = 0; l < 4; l++){
                char posicao[2];

                getPosicao(false, i, j, (*navio).tamanho, l, posicao, automatico);

                posicaoValidaF = verificaPosicao(false, (*jogador).tabuleiro, automatico, (*navio).tamanho, 
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
            for (int l = 0; l < (*navio).tamanho; l++){
                (*jogador).tabuleiro[i-64][j-47+l] = (*navio).classe;
            }
        } else {
            for (int l = 0; l < (*navio).tamanho; l++){
                (*jogador).tabuleiro[i-64][j-47-l] = (*navio).classe;
            }
        }
    } else {
        if (i2 > i){
            for (int l = 0; l < (*navio).tamanho; l++){
                (*jogador).tabuleiro[i-64+l][j-47] = (*navio).classe;
            }
        } else {
            for (int l = 0; l < (*navio).tamanho; l++){
                (*jogador).tabuleiro[i-64-l][j-47] = (*navio).classe;
            }
        }
    }

    for (int l = 0; l < (*navio).tamanho; l++){
        if (i == i2){
            (*navio).posicao[l][0] = i;
            (*navio).posicao[l][1] = j + l;
        } else {
            (*navio).posicao[l][0] = i + l;
            (*navio).posicao[l][1] = j;
        }
    }

    if ((*jogador).humano == true && automatico == false){ 
        imprimeInventario();
        (*jogo).modoJogo == 1 ? imprimeTabuleiro((*jogador).tabuleiro) : imprimeTabuleiro((*jogo).tabuleiro);
    } else if ((*jogador).humano == true && automatico == true) { 
        printf("\nPreenchendo tabuleiro...");
        if((*jogo).modoJogo == 1){
            imprimeTabuleiro((*jogador).tabuleiro);
        }
    } else {
        printf("\nAguardando computador...");
    }

}

bool verificaSeAfundou(char navio, char tabuleiro[TAMANHO][TAMANHO]){

    int contador = 0;

    for (int i = 1; i < TAMANHO; i++){
        for (int j = 1; j < TAMANHO; j++){
            if (tabuleiro[i][j] == navio){
                contador += 1;
            }
        }
    }

    if (contador <= 1){
        return true;
    } else {
        return false;
    }

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
                    jogadaValida = false;
                } else if (j > 57 || j < 48){
                    jogadaValida = false;
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

                printf("\n%s %s Acertou!\n", (*computador).titulo, (*computador).nome);

                if (verificaSeAfundou((*jogador).tabuleiro[i-64][j-47], (*jogador).tabuleiro)){

                    char nomeNavio[20];

                    recuperaNomeNavio((*jogador).tabuleiro[i-64][j-47], nomeNavio);

                    printf("\nAfundou o %s\n", nomeNavio);
                }

                (*jogador).tabuleiro[i-64][j-47] = '*';
                (*computador).pontuacao += 1;
                (*computador).acertouAnterior = true;
            } else {

                (*jogador).tabuleiro[i-64][j-47] = 'X';
                (*computador).acertouAnterior = false;

                printf("\n%s %s Errou\n", (*computador).titulo, (*computador).nome);
            }

            imprimeTabuleiro((*jogador).tabuleiro);
            printf("Tabuleiro de %s %s", (*jogador).titulo, (*jogador).nome );

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
                        jogadaValida = false;
                    } else if (j > 57 || j < 48){
                        jogadaValida = false;
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

                    printf("\n%s %s Acertou!\n", (*computador).titulo, (*computador).nome);

                    if (verificaSeAfundou((*jogador).tabuleiro[i-64][j-47], (*jogador).tabuleiro)){

                        char nomeNavio[20];

                        recuperaNomeNavio((*jogador).tabuleiro[i-64][j-47], nomeNavio);

                        printf("\nAfundou o %s\n", nomeNavio);
                    }

                    (*jogador).tabuleiro[i-64][j-47] = '*';
                    (*computador).pontuacao += 1;
                    (*computador).acertouAnterior = true;
                } else {
                    (*jogador).tabuleiro[i-64][j-47] = 'X';
                    (*computador).acertouAnterior = false;

                    printf("\n%s %s Errou\n", (*computador).titulo, (*computador).nome);
                }

                imprimeTabuleiro((*jogador).tabuleiro);
                printf("Tabuleiro de %s %s", (*jogador).titulo, (*jogador).nome );

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
                        jogadaValida = false;
                    } else if (j > 57 || j < 48){
                        jogadaValida = false;
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

                    printf("\n%s %s Acertou!\n", (*computador).titulo, (*computador).nome);

                    if (verificaSeAfundou((*jogador).tabuleiro[i-64][j-47], (*jogador).tabuleiro)){

                        char nomeNavio[20];

                        recuperaNomeNavio((*jogador).tabuleiro[i-64][j-47], nomeNavio);

                        printf("\nAfundou o %s\n", nomeNavio);
                    }

                    (*jogador).tabuleiro[i-64][j-47] = '*';
                    (*computador).pontuacao += 1;
                    (*computador).acertouAnterior = true;
                } else {
                    (*jogador).tabuleiro[i-64][j-47] = 'X';
                    (*computador).acertouAnterior = false;

                    printf("\n%s %s Errou\n", (*computador).titulo, (*computador).nome);
                }

                imprimeTabuleiro((*jogador).tabuleiro);
                printf("Tabuleiro de %s %s", (*jogador).titulo, (*jogador).nome );

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
                        jogadaValida = false;
                    } else if (j > 57 || j < 48){
                        jogadaValida = false;
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

                    printf("\n%s %s Acertou!\n", (*computador).titulo, (*computador).nome);

                    if (verificaSeAfundou((*jogador).tabuleiro[i-64][j-47], (*jogador).tabuleiro)){

                        char nomeNavio[20];

                        recuperaNomeNavio((*jogador).tabuleiro[i-64][j-47], nomeNavio);

                        printf("\nAfundou o %s\n", nomeNavio);
                    }

                    (*jogador).tabuleiro[i-64][j-47] = '*';
                    (*computador).pontuacao += 1;
                    (*computador).acertouAnterior = true;
                } else {
                    (*jogador).tabuleiro[i-64][j-47] = 'X';
                    (*computador).acertouAnterior = false;

                    printf("\n%s %s Errou\n", (*computador).titulo, (*computador).nome);
                }

                imprimeTabuleiro((*jogador).tabuleiro);
                printf("Tabuleiro de %s %s", (*jogador).titulo, (*jogador).nome );

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
                                jogadaValida = false;
                            } else if (j > 57 || j < 48){
                                jogadaValida = false;
                            } else {
                                jogadaValida = verificaJogada(i, j, (*computador).jogadasRealizadas);
                            }
                        }
                    }
                    

                    if (i > 74 || i < 65){
                        jogadaValida = false;
                    } else if (j > 57 || j < 48){
                        jogadaValida = false;
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

                    printf("\n%s %s Acertou!\n", (*computador).titulo, (*computador).nome);

                    if (verificaSeAfundou((*jogador).tabuleiro[i-64][j-47], (*jogador).tabuleiro)){

                        char nomeNavio[20];

                        recuperaNomeNavio((*jogador).tabuleiro[i-64][j-47], nomeNavio);

                        printf("\nAfundou o %s\n", nomeNavio);
                    }

                    (*jogador).tabuleiro[i-64][j-47] = '*';
                    (*computador).pontuacao += 1;
                    (*computador).acertouAnterior = true;
                } else {
                    (*jogador).tabuleiro[i-64][j-47] = 'X';
                    (*computador).acertouAnterior = false;

                    printf("\n%s %s Errou\n", (*computador).titulo, (*computador).nome);
                }

                imprimeTabuleiro((*jogador).tabuleiro);
                printf("Tabuleiro de %s %s", (*jogador).titulo, (*jogador).nome );

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
                    jogadaValida = false;
                } else if (j > 57 || j < 48){
                    jogadaValida = false;
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

                printf("\n%s %s Acertou!\n", (*computador).titulo, (*computador).titulo);

                if (verificaSeAfundou((*jogador).tabuleiro[i-64][j-47], (*jogador).tabuleiro)){

                    char nomeNavio[20];

                    recuperaNomeNavio((*jogador).tabuleiro[i-64][j-47], nomeNavio);

                    printf("\nAfundou o %s\n", nomeNavio);
                }

                (*jogador).tabuleiro[i-64][j-47] = '*';
                (*computador).pontuacao += 1;
                (*computador).acertouAnterior = true;
            } else {
                (*jogador).tabuleiro[i-64][j-47] = 'X';
                (*computador).acertouAnterior = false;

                printf("\n%s %s Errou\n", (*computador).titulo, (*computador).nome);
            }

            imprimeTabuleiro((*jogador).tabuleiro);
            printf("Tabuleiro de %s %s", (*jogador).titulo, (*jogador).nome );

            break;
    }

}

void realizaDisparo(Jogador *jogador, Jogador *jogadorAlvo, Jogo *jogo){

    char i, j;

    bool jogadaValida = false;

    while (jogadaValida == false){

        char posicao[2], c;

        int w = 0;
        if ( (*jogador).acertouAnterior == false ){
            printf("\n %s %s, digite a posicao para disparo!\n", (*jogador).titulo, (*jogador).nome);
        }

        printf("Posicao: ");

        while ( (c = getchar() ) != '\n' && c != EOF){
            posicao[w] = c;
            w++;
        }

        i = posicao[0];
        j = posicao[1];

        if (i > 74 || i < 65){
            printf("\nDigite uma posicao valida!\n");
        } else if (j > 57 || j < 48){
            printf("\nDigite uma posicao valida!\n");
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

        printf("\n%s %s Acertou!\n", (*jogador).titulo, (*jogador).nome);

        if (verificaSeAfundou((*jogadorAlvo).tabuleiro[i-64][j-47], (*jogadorAlvo).tabuleiro)){

            char nomeNavio[20];

            recuperaNomeNavio((*jogadorAlvo).tabuleiro[i-64][j-47], nomeNavio);

            printf("Afundou o %s Inimigo!", nomeNavio);
        }

        (*jogadorAlvo).tabuleiro[i-64][j-47] = '*';
        (*jogador).pontuacao += 1;
        (*jogador).acertouAnterior = true;

    } else {
        (*jogadorAlvo).tabuleiro[i-64][j-47] = 'X';
        (*jogador).acertouAnterior = false;
        printf("\n%s %s Errou!\n", (*jogador).titulo, (*jogador).nome);
    }

    imprimeTabuleiroOculto((*jogadorAlvo).tabuleiro);
    printf("Tabuleiro de %s %s\n", (*jogadorAlvo).titulo, (*jogadorAlvo).nome );
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

    Navio submarino = setNavio("Submarino", 'S', 2);

    Navio destroyer = setNavio("Destroyer", 'D', 3);

    Navio cruzador = setNavio("Cruzador", 'C', 4);

    Navio portaAviao = setNavio("Porta-Avioes", 'P', 5);
  
    Jogo jogo = setJogo();

    if (jogo.modoJogo == 1){
        Jogador jogador1 = setJogador(humano, "humano");

        printf("\n\nJogador %s %s\n", jogador1.titulo, jogador1.nome);
        
        Jogador computador = setJogador(comp, "CPU");

        printf("\n\nAdversario %s %s\n", computador.titulo, computador.nome);

        setTabuleiro(&computador, &submarino, &jogo, true);

        setTabuleiro(&computador, &destroyer, &jogo, true);

        setTabuleiro(&computador, &cruzador, &jogo, true);

        setTabuleiro(&computador, &portaAviao, &jogo, true);

        bool satisfeito = false;

        while (satisfeito == false){

            printf("\nDeseja que o computador preencha o Tabuleiro para voce?\n");

            printf("\n [1] - Sim!");
            printf("\n [2] - Nao!\n");

            int escolhaAuto = 0;

            while (escolhaAuto != 1 && escolhaAuto != 2){

                printf("\nEscolha: ");

                char dif, c;

                while ( (c = getchar() ) != '\n' && c != EOF){
                    dif = c;
                }

                escolhaAuto = (dif - 48);

                if (escolhaAuto != 1 && escolhaAuto != 2){
                    printf("\nEscolha Invalida!\n");
                }

            } 

            bool automatico = false;

            if (escolhaAuto == 1){
                automatico = true;
            } else {
                imprimeInventario();

                imprimeTabuleiro(jogador1.tabuleiro);
            }

            setTabuleiro(&jogador1, &submarino, &jogo, automatico);

            setTabuleiro(&jogador1, &destroyer, &jogo, automatico);

            setTabuleiro(&jogador1, &cruzador, &jogo, automatico);

            setTabuleiro(&jogador1, &portaAviao, &jogo, automatico);

            printf("\nEsta satisfeito ou deseja recolocar os navios?\n");

            int escolha = 0;

            printf("\n [1] - Sim, estou satisfeito!");
            printf("\n [2] - Nao, quero alterar!\n");

            while (escolha != 1 && escolha != 2){

                printf("\nEscolha: ");

                char dif, c;

                while ( (c = getchar() ) != '\n' && c != EOF){
                    dif = c;
                }

                escolha = (dif - 48);

                if (escolha != 1 && escolha != 2){
                    printf("\nEscolha Invalida!\n");
                }

            }

            if (escolha == 1){
                satisfeito = true;
            } else{
                preencheTabuleiro(jogador1.tabuleiro);
            }

        }


        while (jogador1.pontuacao != PONTUACAO_MAX && computador.pontuacao != PONTUACAO_MAX){
            
            printf("\n");

            jogador1.jogadas += 1;
            realizaDisparo(&jogador1, &computador, &jogo);

            while (jogador1.acertouAnterior == true && jogador1.pontuacao != PONTUACAO_MAX){

                printf("\nPontos %s %s: %d\n", jogador1.titulo, jogador1.nome, jogador1.pontuacao);

                printf("\nComo Acertou a anterior, realize novo disparo:\n");

                jogador1.jogadas += 1;
                realizaDisparo(&jogador1, &computador, &jogo);
                printf("\n");
            }

            printf("\n");

            if (jogador1.pontuacao == PONTUACAO_MAX){
                printf("\nPontos %s %s: %d\n", jogador1.titulo, jogador1.nome, jogador1.pontuacao);
                printf("\nVENCEDOR: %s %s\n", jogador1.titulo, jogador1.nome);
                return 0;
            } else if (computador.pontuacao == PONTUACAO_MAX){
                printf("\nPontos %s %s: %d\n", computador.titulo, computador.nome, computador.pontuacao);
                printf("\nVENCEDOR: %s CPU\n", computador.titulo);
                return 0;
            }

            printf("\nAguardando jogada do Computador....");

            computador.jogadas += 1;
            realizaDisparoIA(&computador, &jogador1, jogo.dificuldade, computador.jogadas-2);

            while (computador.acertouAnterior == true && computador.pontuacao != PONTUACAO_MAX){

                printf("\nPontos %s %s: %d\n", computador.titulo, computador.nome, computador.pontuacao);

                printf("\nComo Acertou a anterior, realize novo disparo:\n");
                printf("\nAguardando jogada do Computador....");

                computador.jogadas += 1;
                realizaDisparoIA(&computador, &jogador1, jogo.dificuldade, computador.jogadas-2);
                printf("\n");

            }

            if (jogador1.pontuacao == PONTUACAO_MAX){
                printf("\nPontos %s %s: %d\n", jogador1.titulo, jogador1.nome, jogador1.pontuacao);
                printf("\nVENCEDOR: %s %s\n", jogador1.titulo, jogador1.nome);
                return 0;
            } else if (computador.pontuacao == PONTUACAO_MAX){
                printf("\nPontos %s %s: %d\n", computador.titulo, computador.nome, computador.pontuacao);
                printf("\nVENCEDOR: %s CPU\n", computador.titulo);
                return 0;
            }
            
        }

    } else if (jogo.modoJogo == 2) {

        Jogador jogador1 = setJogador(humano, "humano");

        printf("\n\nJogador %s %s\n", jogador1.titulo, jogador1.nome);
        
        bool satisfeito = false;

        while (satisfeito == false){

            printf("\nDeseja que o computador preencha o Tabuleiro para voce?\n");

            printf("\n [1] - Sim!");
            printf("\n [2] - Nao!\n");

            int escolhaAuto = 0;

            while (escolhaAuto != 1 && escolhaAuto != 2){

                printf("\nEscolha: ");

                char dif, c;

                while ( (c = getchar() ) != '\n' && c != EOF){
                    dif = c;
                }

                escolhaAuto = (dif - 48);

                if (escolhaAuto != 1 && escolhaAuto != 2){
                    printf("\nEscolha Invalida!\n");
                }

            } 

            bool automatico = false;

            if (escolhaAuto == 1){
                automatico = true;
            } else {
                imprimeInventario();

                imprimeTabuleiro(jogo.tabuleiro);
            }

            setTabuleiro(&jogador1, &submarino, &jogo, automatico);

            setTabuleiro(&jogador1, &destroyer, &jogo, automatico);

            setTabuleiro(&jogador1, &cruzador, &jogo, automatico);

            setTabuleiro(&jogador1, &portaAviao, &jogo, automatico);

            printf("\nEsta satisfeito ou deseja recolocar os navios?\n");

            int escolha = 0;

            printf("\n [1] - Sim, estou satisfeito!");
            printf("\n [2] - Nao, quero alterar!\n");

            while (escolha != 1 && escolha != 2){

                printf("\nEscolha: ");

                char dif, c;

                while ( (c = getchar() ) != '\n' && c != EOF){
                    dif = c;
                }

                escolha = (dif - 48);

                if (escolha != 1 && escolha != 2){
                    printf("\nEscolha Invalida!\n");
                }

            }

            if (escolha == 1){
                satisfeito = true;
            } else{
                preencheTabuleiro(jogador1.tabuleiro);
            }

        }

        printf("\nAgora, ao oponente!\n");

        Jogador jogador2 = setJogador(humano, "humano");

        printf("\n\nAdversario %s %s\n", jogador2.titulo, jogador2.nome);

        satisfeito = false;

        while (satisfeito == false){

            printf("\nDeseja que o computador preencha o Tabuleiro para voce?\n");

            printf("\n [1] - Sim!");
            printf("\n [2] - Nao!\n");

            int escolhaAuto = 0;

            while (escolhaAuto != 1 && escolhaAuto != 2){

                printf("\nEscolha: ");

                char dif, c;

                while ( (c = getchar() ) != '\n' && c != EOF){
                    dif = c;
                }

                escolhaAuto = (dif - 48);

                if (escolhaAuto != 1 && escolhaAuto != 2){
                    printf("\nEscolha Invalida!\n");
                }

            } 

            bool automatico = false;

            if (escolhaAuto == 1){
                automatico = true;
            } else {
                imprimeInventario();

                imprimeTabuleiro(jogo.tabuleiro);
            }

            setTabuleiro(&jogador2, &submarino, &jogo, automatico);

            setTabuleiro(&jogador2, &destroyer, &jogo, automatico);

            setTabuleiro(&jogador2, &cruzador, &jogo, automatico);

            setTabuleiro(&jogador2, &portaAviao, &jogo, automatico);

            printf("\nEsta satisfeito ou deseja recolocar os navios?\n");

            int escolha = 0;

            printf("\n [1] - Sim, estou satisfeito!");
            printf("\n [2] - Nao, quero alterar!\n");

            while (escolha != 1 && escolha != 2){

                printf("\nEscolha: ");

                char dif, c;

                while ( (c = getchar() ) != '\n' && c != EOF){
                    dif = c;
                }

                escolha = (dif - 48);

                if (escolha != 1 && escolha != 2){
                    printf("\nEscolha Invalida!\n");
                }

            }

            if (escolha == 1){
                satisfeito = true;
            } else{
                preencheTabuleiro(jogador2.tabuleiro);
            }

        }

        while (jogador1.pontuacao != PONTUACAO_MAX && jogador2.pontuacao != PONTUACAO_MAX){
            
            printf("\n");

            jogador1.jogadas += 1;
                realizaDisparo(&jogador1, &jogador2, &jogo);

            while (jogador1.acertouAnterior == true && jogador1.pontuacao != PONTUACAO_MAX){

                printf("\nPontos %s %s: %d\n", jogador1.titulo, jogador1.nome, jogador1.pontuacao);

                printf("\nComo voce acertou a anterior, realize novo disparo:\n");

                jogador1.jogadas += 1;
                realizaDisparo(&jogador1, &jogador2, &jogo);
                printf("\n");
            }

            printf("\n");

            if (jogador1.pontuacao == PONTUACAO_MAX){
                printf("\nPontos %s %s: %d\n", jogador1.titulo, jogador1.nome, jogador1.pontuacao);
                printf("\n VENCEDOR: %s %s \n", jogador1.titulo, jogador1.nome);
                return 0;
            } else if (jogador2.pontuacao == PONTUACAO_MAX){
                printf("\nPontos %s %s: %d\n", jogador2.titulo, jogador2.nome, jogador2.pontuacao);
                printf("\n VENCEDOR: %s %s \n", jogador2.titulo, jogador2.nome);
                return 0;
            }

            jogador2.jogadas += 1;
                realizaDisparo(&jogador2, &jogador1, &jogo);

            while (jogador2.acertouAnterior == true && jogador2.pontuacao != PONTUACAO_MAX){

                printf("\nPontos %s %s: %d\n", jogador2.titulo, jogador2.nome, jogador2.pontuacao);

                printf("\nComo voce acertou a anterior, realize novo disparo:\n");

                jogador2.jogadas += 1;
                realizaDisparo(&jogador2, &jogador1, &jogo);
                printf("\n");
            }

            if (jogador1.pontuacao == PONTUACAO_MAX){
                printf("\nPontos %s %s: %d\n", jogador1.titulo, jogador1.nome, jogador1.pontuacao);
                printf("\n VENCEDOR: %s %s \n", jogador1.titulo, jogador1.nome);
                return 0;
            } else if (jogador2.pontuacao == PONTUACAO_MAX){
                printf("\nPontos %s %s: %d\n", jogador2.titulo, jogador2.nome, jogador2.pontuacao);
                printf("\n VENCEDOR: %s %s \n", jogador2.titulo, jogador2.nome);
                return 0;
            }

        }

    } else if (jogo.modoJogo == 3) {

        Jogador computador = setJogador(comp, "CPU 1");

        printf("\n\nAdversario %s %s\n", computador.titulo, computador.nome);

        setTabuleiro(&computador, &submarino, &jogo, true);

        setTabuleiro(&computador, &destroyer, &jogo, true);

        setTabuleiro(&computador, &cruzador, &jogo, true);

        setTabuleiro(&computador, &portaAviao, &jogo, true);

        Jogador computador2 = setJogador(comp, "CPU 2");

        printf("\n\nAdversario %s %s\n", computador2.titulo, computador2.nome);

        setTabuleiro(&computador2, &submarino, &jogo, true);

        setTabuleiro(&computador2, &destroyer, &jogo, true);

        setTabuleiro(&computador2, &cruzador, &jogo, true);

        setTabuleiro(&computador2, &portaAviao, &jogo, true);


        while (computador.pontuacao != PONTUACAO_MAX && computador2.pontuacao != PONTUACAO_MAX){
            
            printf("\n");

            printf("\nAguardando jogada do Computador....");

            computador.jogadas += 1;

            realizaDisparoIA(&computador, &computador2, jogo.dificuldade, computador.jogadas-2);

            while (computador.acertouAnterior == true && computador.pontuacao != PONTUACAO_MAX){

                printf("\nPontos %s %s: %d\n", computador.titulo, computador.nome, computador.pontuacao);

                printf("\nComo Acertou a anterior, realize novo disparo:\n");
                printf("\nAguardando jogada do Computador....");

                computador.jogadas += 1;
                realizaDisparoIA(&computador, &computador2, jogo.dificuldade, computador.jogadas-2);

                printf("\n");

            }

            printf("\n");

            if (computador.pontuacao == PONTUACAO_MAX){
                printf("\nPontos %s %s: %d\n", computador.titulo, computador.nome, computador.pontuacao);
                printf("\n VENCEDOR: %s CPU1 \n", computador.titulo);
                return 0;
            } else if (computador2.pontuacao == PONTUACAO_MAX){
                printf("\nPontos %s %s: %d\n", computador2.titulo, computador2.nome, computador2.pontuacao);
                printf("\n VENCEDOR: %s CPU2 \n", computador2.titulo);
                return 0;
            }

            printf("\nAguardando jogada do Computador....");            

            computador2.jogadas += 1;
            realizaDisparoIA(&computador2, &computador, jogo.dificuldade, computador2.jogadas-2);

            while (computador2.acertouAnterior == true && computador2.pontuacao != PONTUACAO_MAX){

                printf("\nPontos %s %s: %d\n", computador2.titulo, computador2.nome, computador2.pontuacao);

                printf("\nComo Acertou a anterior, realize novo disparo:\n");
                printf("\nAguardando jogada do Computador....");

                computador2.jogadas += 1;
                realizaDisparoIA(&computador2, &computador, jogo.dificuldade, computador2.jogadas-2);
                printf("\n");

            }

            if (computador.pontuacao == PONTUACAO_MAX){
                printf("\nPontos %s %s: %d\n", computador.titulo, computador.nome, computador.pontuacao);
                printf("\n VENCEDOR: %s CPU1 \n", computador.titulo);
                return 0;
            } else if (computador2.pontuacao == PONTUACAO_MAX){
                printf("\nPontos %s %s: %d\n", computador2.titulo, computador2.nome, computador2.pontuacao);
                printf("\n VENCEDOR: %s CPU2 \n", computador2.titulo);
                return 0;
            }

        }

    }

    return 0;
}
