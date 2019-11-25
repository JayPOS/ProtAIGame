#include "../includes/editor.hpp"
#include "../includes/aux.hpp"


Editor *inicia_mapa(Editor* editor)
{
    // LINHAS
    for (int i = 0; i < 31; i++)
    {
        // COLUNAS
        for (int j = 0; j < 28; j++)
        {
            // cout << " aa" << " i = " << i << " j = " << j << "\n";
            editor->squares[i][j].x = j*16;
            editor->squares[i][j].y = i*16;
            editor->squares[i][j].w = (j+1)*16;
            editor->squares[i][j].h = (i+1)*16;

            editor->id_squares[i][j] = 0;
        }
    }
    return editor;
}

SDL_Texture *loadTextureFromIMG(Editor *editor2, char *path, SDL_Renderer *renderer)
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
    
    editor2->pacman = carregaPacman(editor2->pacman, renderer);

    return editor2->mapa;
}

SDL_Texture *getMapa(Editor *editor)
{
    return editor->mapa;
}

void salvaEstado(Editor *editor)
{
    FILE *file = fopen("./info/squares", "wb");
    for (int i = 0; i < 31; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            fwrite(&editor->id_squares[i][j], sizeof(int), 1, file);
        }
    }
    fclose(file);
}
Editor *abreEstado(Editor *editor)
{
    FILE *file = fopen("./info/squares", "rb");
    for (int i = 0; i < 31; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            fread(&editor->id_squares[i][j], sizeof(int), 1, file);
            cout << editor->id_squares[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    fclose(file);
    return editor;
}

void desenhaLinhas(Editor *editor, SDL_Renderer *renderer)
{
    // DESENHA HORIZONTAL
    for (int i = 0; i < 31; i++)
    {
        SDL_RenderDrawLine(renderer, 0, editor->squares[i][0].y, 448, editor->squares[i][0].y);
    }
    // DESENHA VERTICAL
    for (int i = 0; i < 28; i++)
    {
        SDL_RenderDrawLine(renderer, editor->squares[0][i].x, 0, editor->squares[0][i].x, 496);
    }
}

void estadoEditor(Editor *editor, SDL_Renderer *renderer)
{
    SDL_Rect aux;
    for (int i = 0; i < 31; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            if (editor->id_squares[i][j] == FOOD)
            {
                aux.x = editor->squares[i][j].x;
                aux.y = editor->squares[i][j].y;
                aux.w = 16;
                aux.h = 16;
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 150);
                SDL_RenderFillRect(renderer, &aux);
                // cout << "FOOD\n";
                // cout << "id = ";
                // cout << editor->id_squares[i][j] << " Rects = ";
                // cout << i << " ";
                // cout << j << "\n";
            }
            else if (editor->id_squares[i][j] == WALL)
            {
                aux.x = editor->squares[i][j].x;
                aux.y = editor->squares[i][j].y;
                aux.w = 16;
                aux.h = 16;
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 150);
                SDL_RenderFillRect(renderer, &aux);
                // cout << "WALL\n";
                // cout << "id = ";
                // cout << editor->id_squares[i][j] << " Rects = ";
                // cout << i << " ";
                // cout << j << "\n";
            }
            else if (editor->id_squares[i][j] == BIG_FOOD)
            {
                aux.x = editor->squares[i][j].x;
                aux.y = editor->squares[i][j].y;
                aux.w = 16;
                aux.h = 16;
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 150);
                SDL_RenderFillRect(renderer, &aux);
            }
        }
    }
}

void desenhaEditor(Editor *editor, SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
    SDL_Rect drecto = {0, 0, 448, 496};
    SDL_RenderCopy(renderer, editor->mapa, NULL, &drecto);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    desenhaLinhas(editor, renderer);
    estadoEditor(editor, renderer);
    SDL_RenderPresent(renderer);
}


void eventosEditor(Editor **editor, SDL_Renderer *renderer, SDL_Event *e, bool &on)
{
    int control;
    while (SDL_PollEvent(e) != 0)
    {
        control = 0;
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
                case SDLK_RETURN:
                    //salva matriz
                    salvaEstado(*editor);
                    abreEstado(*editor);
                    break;
                case SDLK_SPACE:
                    abreEstado(*editor);
                    break;
                }
                break;
			}
            case SDL_MOUSEBUTTONDOWN:
                switch (e->button.button)
                {
                    case SDL_BUTTON_LEFT:
                    for (int i = 0; i < 31; i++)
                    {
                        for (int j = 0; j < 28; j++)
                        {
                            if (e->button.x > editor[0]->squares[i][j].x 
                            && e->button.x < editor[0]->squares[i][j].w 
                            && e->button.y > editor[0]->squares[i][j].y 
                            && e->button.y < editor[0]->squares[i][j].h)
                            {
                                cout << i << " " << j << "\n";
                                editor[0]->id_squares[i][j]++;
                                editor[0]->id_squares[i][j] = editor[0]->id_squares[i][j]%4;
                                cout << editor[0]->id_squares[i][j] << "\n";
                                control = 1;
                                break;
                            }
                        }
                        if (control == 1)
                            break;
                    }
                    break;
            } 
            break;   
        }
    }
}