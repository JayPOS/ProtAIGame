#ifndef GHOST_HPP
#define GHOST_HPP

#include "includes.hpp"
#include "astar.hpp"

typedef struct ghost Fantasma;
struct ghost
{
    // first = i, second = j;
    SDL_Texture *textura;
    SDL_Rect frames[8];
    int i, j; //rect
    int x, y; //coordinates
    ii center; // center of the ghost
    int vel;
    int pts, cor, dir;
    vector<No> caminho;
};

const int RED = 0;
const int PINK = 1;
const int BLUE = 2;
const int YELLOW = 3;


Fantasma criaFantasma(Fantasma fant, SDL_Renderer *renderer, int id);   
/*  checa os vizinhos, faz a distancia de manhatan de onde o pacman ta pro fantasma, ve os vizinhos
adiciona o vizinho cuja distancia de manhatam até o local do pacman que tava marcado, 
*/

void terminaGhost(Fantasma fantasma);
#endif