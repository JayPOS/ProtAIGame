#include "../includes/editor.hpp"
#include "../includes/aux.hpp"

SDL_Texture *loadTextureFromIMG(Editor *editor2, char *path, SDL_Window *janela, SDL_Renderer *renderer)
{    
    SDL_Surface *surface = NULL;
    surface = IMG_Load(path);  
    if (surface == NULL)
    {
        cout << "ERRO_LOADING_IMG: " << path << "\n";
        cout << IMG_GetError() << "\n";
        return NULL;
    }
    editor2->mapa = NULL;
    editor2->mapa = SDL_CreateTextureFromSurface(renderer, surface);
    if (editor2->mapa == NULL)
    {
        cout << "Erro!!! Parando programa...\n";
    }
    SDL_FreeSurface(surface);
    return editor2->mapa;
}

SDL_Texture *getMapa(Editor *editor)
{
    return editor->mapa;
}

bool desenhaEditor(Editor *editor, SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
    SDL_Rect drecto = {0, 0, 448, 496};
    SDL_RenderCopy(renderer, editor->mapa, NULL, &drecto);
    SDL_RenderPresent(renderer);

}