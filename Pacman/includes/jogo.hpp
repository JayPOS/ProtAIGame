#ifndef JOGO_HPP_
#define JOGO_HPP_
#include "includes.hpp"
#include "pacman.hpp"

typedef struct game Jogo;
struct jogo
{
    Pacman *player;
    //Fantasmas inimigos[4];
    SDL_Texture *mapa;
    SDL_Rect squares[31][28];
    int id_squares;
};

void carregarJogo(Jogo **jogo);

void desenharJogo(Jogo *jogo, SDL_Renderer *renderer);

Jogo* movimentosPacman(Jogo *jogo);
//Jogo *movimentosGhost(Jogo *jogo);
Jogo *colisao(Jogo *);

#endif