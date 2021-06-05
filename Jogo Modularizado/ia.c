#include "ia.h"

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
