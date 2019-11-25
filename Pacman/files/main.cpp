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
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_Event e;
            bool on = true;
            char aux[70] = "./pacman_images/mapa.png";

            loadTextureFromIMG(editor, aux, renderer);
            editor = inicia_mapa(editor);

            FILE *file = fopen("./info/teste.txt", "w");
            char teste[200];
            for (int i = 0; i < 31; i++)
            {
                // COLUNAS
                for (int j = 0; j < 28; j++)
                {
                    sprintf(teste, "Rects x,y,w,h = %d,%d,%d,%d\n", editor->squares[i][j].x
                    , editor->squares[i][j].y, editor->squares[i][j].w, editor->squares[i][j].h);
                    fprintf(file, "%s", teste);
                    cout << editor->id_squares[i][j] << "\nRects = ";
                    cout << editor->squares[i][j].x << " ";
                    cout << editor->squares[i][j].y << " ";
                    cout << editor->squares[i][j].w << " ";
                    cout << editor->squares[i][j].h << "\n";
                }
            }
            fclose(file);

            while (on)
            {
                if (getMapa(editor) == NULL)
                {
                    cout << "Erro!!! Parando programa...\n";
                    on = false;
                }
                desenhaEditor(editor, renderer);
                eventosEditor(&editor, renderer, &e, on);
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