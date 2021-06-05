#include "ia.h"

int main(){

    int humano = 1;
    int comp = 0;

    Jogo jogo = setJogo();

    Jogador jogador1 = setJogador(humano);

    printf("\n\nJogador %s %s\n", jogador1.titulo, jogador1.nome);


    if (jogo.modoJogo == 1){

        Jogador computador = setJogador(comp);

        printf("\n\nAdversario %s %s\n", computador.titulo, computador.nome);

        Navio submarinoComputador = setNavio(&computador, "Submarino", 'S', 2);

        Navio destroyerComputador = setNavio(&computador, "Destroyer", 'D', 3);

        Navio cruzadorComputador = setNavio(&computador, "Cruzador", 'C', 4);

        Navio portaAviaoComputador = setNavio(&computador, "Porta-Aviões", 'P', 5);

        imprimeTabuleiro(jogador1.tabuleiro);

        Navio submarinoJogador = setNavio(&jogador1, "Submarino", 'S', 2);

        Navio destroyerJogador = setNavio(&jogador1, "Destroyer", 'D', 3);

        Navio cruzadorJogador = setNavio(&jogador1, "Cruzador", 'C', 4);

        Navio portaAviaoJogador = setNavio(&jogador1, "Porta-Aviões", 'P', 5);

        while (jogo.rodada != 50){

            realizaDisparo(&jogador1, &computador);

            realizaDisparoIA(&computador, &jogador1, jogo.dificuldade, jogo.rodada-2);

            jogo.rodada += 1;
        }

    } else {

        Jogador jogador2 = setJogador(humano);

        printf("\n\nAdversario %s %s\n", jogador2.titulo, jogador2.nome);

        Navio submarinoJogador2 = setNavio(&jogador2, "Submarino", 'S', 2);

        Navio destroyerJogador2 = setNavio(&jogador2, "Destroyer", 'D', 3);

        Navio cruzadorJogador2= setNavio(&jogador2, "Cruzador", 'C', 4);

        Navio portaAviaoJogador2 = setNavio(&jogador2, "Porta-Aviões", 'P', 5);

        imprimeTabuleiro(jogador2.tabuleiro);

        while (jogo.rodada != 50){

            realizaDisparo(&jogador1, &jogador2);

            realizaDisparo(&jogador2, &jogador1);

            jogo.rodada += 1;
        }

    }

    return 0;
}
