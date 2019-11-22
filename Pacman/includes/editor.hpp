#ifndef _EDITOR_HPP_
#define _EDITOR_HPP_
#include "sdl_functions.hpp"
#include <cstdlib>

const int STREET = 0;
const int FOOD = 1;
const int BORDER = 2;

const int LINHAS = 31;
const int COLUNAS = 28;

typedef struct editor Editor;
struct editor
{
    int id_squares[LINHAS][COLUNAS];
    SDL_Texture *mapa;
    SDL_Rect mapa_size;
    SDL_Renderer *renderer;
    SDL_Rect squares[LINHAS][COLUNAS];
};

    void inicia_mapa(SDL_Rect ***squares, int ***id_squares);
    int **inicia_squares(int **id_squares);
    SDL_Rect **calculaMapa(Editor *editor, SDL_Rect **squares);
    SDL_Texture *loadTextureFromIMG(Editor *editor, char *path, SDL_Window *janela, SDL_Renderer *renderer);
    bool desenhaEditor(Editor *editor, SDL_Renderer *renderer);

    SDL_Texture *getTexture(Editor *editor);
    SDL_Texture *getMapa(Editor *editor);
    SDL_Rect **getSquares(Editor *editor);
    

#endif