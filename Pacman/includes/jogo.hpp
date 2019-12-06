#ifndef JOGO_HPP_
#define JOGO_HPP_
#include "includes.hpp"
#include "pacman.hpp"
#include "ghost.hpp"
#include "astar.hpp"

typedef struct jogo Jogo;
struct jogo
{
    Pacman *pacman;
    Fantasma inimigos[4];
    int nivel;
    SDL_Texture *mapa;
    SDL_Rect squares[31][28];
    int id_squares[31][28];

    int prox_move;
};

Jogo *carregarJogo(Jogo *jogo, char *path, SDL_Renderer *renderer);

void desenharJogo(Jogo *jogo, SDL_Renderer *renderer);
void desenhaLinhas(Jogo *jogo, SDL_Renderer *renderer);
void desenharGhost(SDL_Rect sqr[][28], Fantasma *fant, SDL_Renderer *renderer);

void eventosJogo(Jogo **jogo, bool &on);
bool colisao(Jogo *jogo);
bool colisao2(Jogo *jogo);

Fantasma *movimento1(SDL_Rect **squares, Fantasma *fant);
void movimentosGhost(Jogo **jogo); // aqui tem a IA;

//aux
ii center(Jogo *jogo); // centro do rect
SDL_Rect repara_pos(ii center, int w, int h);

void terminaJogo(Jogo *jogo);

#endif