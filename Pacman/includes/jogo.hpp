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
    SDL_Texture **comidas;
    SDL_Rect squares[31][28];
    int id_squares[31][28];

    int prox_move;
};

Jogo *carregarJogo(Jogo *jogo, char *path, SDL_Renderer *renderer);

void desenharJogo(Jogo *jogo, SDL_Renderer *renderer);
void desenhaLinhas(Jogo *jogo, SDL_Renderer *renderer);
void desenharGhost(SDL_Rect sqr[][28], Fantasma *fant, SDL_Renderer *renderer);
void desenhaComidas(SDL_Rect sqr[][28], SDL_Texture **comidas, SDL_Renderer *renderer, int id_sqr[][28]);

void eventosJogo(Jogo **jogo, bool &on);
bool colisao(Jogo *jogo);
bool colisao2(Jogo *jogo);

Fantasma *movimento1(SDL_Rect **squares, Fantasma *fant);
// sub moves
Jogo *chase(Jogo *jogo, int id); // ghost corre atras do pacman
Jogo *fear(Jogo *jogo, int id); // ghost foge do pacman
Jogo *scatter(Jogo *jogo); // ghost se espalha pelo mapa
Jogo *movimentosGhost(Jogo *jogo); // aqui tem a IA;

//aux
ii center(int x, int y, int w, int h); // centro do rect
ii destPinky(int pac_i, int pac_j, int direcao, int id_sqr[][28]);
SDL_Rect repara_pos(ii center, int w, int h);

void terminaJogo(Jogo *jogo);

#endif