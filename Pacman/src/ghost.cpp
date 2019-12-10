#include "../includes/ghost.hpp"

Fantasma criaFantasma(Fantasma fant, SDL_Renderer *renderer, int id)
{
    SDL_Surface *surface = NULL;
    surface = IMG_Load("./pacman_images/4ghosts.png");
    fant.textura = SDL_CreateTextureFromSurface(renderer, surface);

    fant.vel = 2;
    fant.pts = 200;
    fant.cor = id;
    fant.dir = STOP;

    for (int i = 0; i < 8; i++)
    {
        fant.frames[i] = {i*16, id*16, 16, 16};
        cout << "Rect---id = " << i*16 << " " << id*16 << " " << (i+1)*16 << " " << (id+1)*16 << "--- id = " << id << "\n";
    }

    SDL_FreeSurface(surface);

    return fant;
}

int distManhatan(ii par1, ii par2)
{
    return sqrt((pow((par1.first-par2.first), 2)+pow((par1.second-par2.second), 2)));
}