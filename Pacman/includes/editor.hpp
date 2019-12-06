#ifndef _EDITOR_HPP_
#define _EDITOR_HPP_
#include "sdl_functions.hpp"
#include "pacman.hpp"
#include <cstdlib>

const int LINHAS = 31;
const int COLUNAS = 28;

typedef struct editor Editor;
struct editor
{
    int id_squares[LINHAS][COLUNAS];
    SDL_Texture *mapa;
    Pacman *pacman;
    SDL_Rect mapa_size;
    SDL_Renderer *renderer;
    SDL_Rect squares[LINHAS][COLUNAS];
    SDL_Point mouse_position;
};

    Editor *inicia_mapa(Editor* editor);
    int **inicia_squares(int **id_squares);
    SDL_Rect **calculaMapa(Editor *editor, SDL_Rect **squares);
    void salvaEstado(Editor *editor);
    Editor *abreEstado(Editor *editor);

    SDL_Texture *loadTextureFromIMG(Editor *editor, char *path, SDL_Renderer *renderer);

    // FUNÇOES DO EDITOR QUE DESENHAM
    void desenhaLinhas(Editor *editor, SDL_Renderer *renderer);
    void estadoRect(Editor *editor, SDL_Renderer *renderer);
    void desenhaEditor(Editor *editor, SDL_Renderer *renderer);

    // EVENTOS DO EDITOR
    void eventosEditor(Editor **editor, SDL_Renderer *renderer, SDL_Event *e, bool &on);

    SDL_Texture *getTexture(Editor *editor);
    SDL_Texture *getMapa(Editor *editor);
    SDL_Rect **getSquares(Editor *editor);
    

#endif