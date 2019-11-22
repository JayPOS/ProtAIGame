#include "../includes/includes.hpp"
#include "../includes/sdl_functions.hpp"
#include "../includes/includes.hpp"
#include "../includes/editor.hpp"
#include <cstdlib>


int main(int argc, char **argv)
{
    if(init())
    {
        Editor *editor = new Editor;
        SDL_Window *janela = NULL;
        if(cria_janela(&janela))
        {
            SDL_Renderer *renderer = NULL;
            renderer = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer ==  NULL)
            {
                cout << "3Erro!!! Parando programa...\n";
                exit(1);
            }
            SDL_Event e;
            bool on = true;
            char aux[70] = "/home/jorge/JayP_Programs/ProtAIGame/Pacman/pacman_images/mapa.png";
            loadTextureFromIMG(editor, aux, janela, renderer);
            while (on)
            {
                if (getMapa(editor) == NULL)
                {
                    cout << "Erro!!! Parando programa...\n";
                    on = false;
                }
                desenhaEditor(editor, renderer);
                // char aux[70] = "/home/jorge/JayP_Programs/ProtAIGame/Pacman/pacman_images/mapa.png";
                // SDL_Surface *surface= NULL;
                // surface= IMG_Load(aux);
                // if (surface == NULL)
                // {
                //     cout << "Erro!!! Parando programa...\n";
                //     on = false;
                // }

                events(&e, &janela, on);
            }
            SDL_DestroyRenderer(renderer);
            renderer = NULL;
            SDL_DestroyWindow(janela);
            janela = NULL;
        }       
    }
    SDL_Quit(); 
    return 0;
}