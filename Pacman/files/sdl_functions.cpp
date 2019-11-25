#include "../includes/sdl_functions.hpp"
#include <cstdlib>

bool init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        cout << "Erro SDL_Init(): " << SDL_GetError() << "\n";
        return false;
    }
    return true;
}
bool quit()
{
    SDL_Quit();
}

bool cria_janela(SDL_Window **janela)
{
    SDL_DisplayMode screen_size;
    SDL_GetCurrentDisplayMode(0, &screen_size);
    // cout << screen_size.w << " " << screen_size.h << "\n";
	*janela = SDL_CreateWindow("Pacman", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        448, 496, 
        SDL_WINDOW_SHOWN);
    if (*janela == NULL)
        {
            cout << "Erro_Criar_Janela = " << SDL_GetError() << "\n";
            return false;
        }
		
        return true;
}
void events(SDL_Event *e, bool &on)
{
	while (SDL_PollEvent(e) != 0 )
	{
		switch(e->type)
		{
			case SDL_QUIT:
				on = false;
				break;
			
			case SDL_KEYDOWN:
			{
				switch (e->key.keysym.sym)
				{
				case SDLK_ESCAPE:
					on = false;
					break;
				
				default:
					break;
				}
			}
		}
	}
}