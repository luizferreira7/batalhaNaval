#include "jogoLogica.h"

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
