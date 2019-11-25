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
    int pos_x, pos_y;
};

Pacman* carregaPacman(Pacman *pacman, SDL_Renderer *renderer);
void movimentos(Pacman *pacman);

#endif