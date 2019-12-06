#ifndef PACMAN_H_
#define PACMAN_H_
#include "includes.hpp"

typedef struct pacman Pacman;
struct pacman
{
    //texturas
    SDL_Texture *texture;
    SDL_Rect *frames;
    // parametros do jogo
    int score;
    int lifes;
    // controle de movimento
    int pos_i, pos_j;
    int pos_x, pos_y;
    int velocidade;
    int direcao;
};

Pacman* carregaPacman(Pacman *pacman, SDL_Renderer *renderer);

#endif