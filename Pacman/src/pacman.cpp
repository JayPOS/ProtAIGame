#include "../includes/pacman.hpp"
#include <cstdlib>

Pacman *carregaPacman(Pacman *pacman, SDL_Renderer *renderer)
{
    pacman = new Pacman;

    // SETANDO PARAMETROS;
    pacman->pos_x = 16;
    pacman->pos_y = 16;
    pacman->direcao = STOP;
    pacman->lifes = 3;
    pacman->score = 0;
    pacman->velocidade = 2;
    // CARREGANDO IMAGENS;
    char path[40] = "./pacman_images/pacmanxcf.png";
    SDL_Surface *surface = NULL;

    surface = IMG_Load(path); 

    if (surface == NULL)
    {
        cout << "ERRO_LOADING_IMG: " << path << "\n";
        cout << IMG_GetError() << "\n";
        return NULL;
    }
    
    pacman->texture = NULL;
    pacman->texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (pacman->texture == NULL)
    {
        cout << "Erro!!! Parando programa...\n";
    }
    SDL_FreeSurface(surface);

    cout << "ooo\n";

    pacman->frames = new SDL_Rect[23];
    for (int i = 0; i < 22; i++)
    {
        cout << i << "\n";
        pacman->frames[i] = {0, i*32, 32, (i+1)*32};
        cout << "PACMAN_RECT = " << pacman->frames[i].x << " "
        << pacman->frames[i].y << " "
        << pacman->frames[i].w << " "
        << pacman->frames[i].h << "\n\n";
    }

    return pacman;
}