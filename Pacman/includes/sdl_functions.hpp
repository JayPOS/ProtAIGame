#ifndef SDL_FUNCTIONS_H_
#define SDL_FUNCTIONS_H_

#include "includes.hpp"

bool init();
bool cria_janela(SDL_Window **janela);
void events(SDL_Event *e, SDL_Window **janela, bool &on);
bool quit();

#endif
