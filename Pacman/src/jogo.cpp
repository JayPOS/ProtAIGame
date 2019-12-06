#include "../includes/jogo.hpp"

ii center(Jogo *jogo)
{
    for (int i = 0; i < 4; i++)
    {
        
        int auxX = jogo->inimigos[i].x;
        int auxY = jogo->inimigos[i].y;

        int squareX = jogo->squares[auxX][auxY].x;
        int squareY = jogo->squares[auxX][auxY].y;
        
        return make_pair(squareX + 8, squareY + 8);
    }
}
Jogo *carregarJogo(Jogo *jogo, char *path, SDL_Renderer *renderer)
{
    SDL_Surface *surface = NULL;
    surface = IMG_Load(path);  
    if (surface == NULL)
    {
        cout << "ERRO_LOADING_IMG: " << path << "\n";
        cout << IMG_GetError() << "\n";
        return NULL;
    }
    jogo->mapa = NULL;
    jogo->mapa = SDL_CreateTextureFromSurface(renderer, surface);
    if (jogo->mapa == NULL)
    {
        cout << "Erro!!! Parando programa...\n";
    }
    SDL_FreeSurface(surface);
    
    jogo->pacman = carregaPacman(jogo->pacman, renderer);
    jogo->nivel = 1;
    jogo->prox_move = 0;

    

    // LINHAS
    FILE *file = fopen("./info/squares", "rb");
    for (int i = 0; i < 31; i++)
    {
        // COLUNAS
        for (int j = 0; j < 28; j++)
        {
            // cout << " aa" << " i = " << i << " j = " << j << "\n";
            jogo->squares[i][j].x = j*16;
            jogo->squares[i][j].y = i*16;
            jogo->squares[i][j].w = (j+1)*16;
            jogo->squares[i][j].h = (i+1)*16;

            fread(&jogo->id_squares[i][j], sizeof(int), 1, file);
            cout << jogo->id_squares[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    
    for (int i = 0; i < 4; i++)
    {
        jogo->inimigos[i] = criaFantasma(jogo->inimigos[i], renderer, i);
        jogo->inimigos[i].x = 14; jogo->inimigos[i].i = (jogo->inimigos[i].x*16)-4;
        jogo->inimigos[i].y = 12;
    }

    fclose(file);

    return jogo;
}

void desenhaLinhas(Jogo *jogo, SDL_Renderer *renderer)
{
    // DESENHA HORIZONTAL
    for (int i = 0; i < 31; i++)
    {
        SDL_RenderDrawLine(renderer, 0, jogo->squares[i][0].y, 448, jogo->squares[i][0].y);
    }
    // DESENHA VERTICAL
    for (int i = 0; i < 28; i++)
    {
        SDL_RenderDrawLine(renderer, jogo->squares[0][i].x, 0, jogo->squares[0][i].x, 496);
    }
}

void desenharGhost(SDL_Rect sqr[][28], Fantasma *fant, SDL_Renderer *renderer)
{
    for (int i = 0; i < 4; i++)
    {
        SDL_Rect aux = {sqr[fant[i].x][fant[i].y].x-4, sqr[fant[i].x][fant[i].y].y-4, 24, 24};
        SDL_RenderCopy(renderer, fant[i].textura, &fant[i].frames[0], &aux);
    }
}

void desenharJogo(Jogo *jogo, SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
    SDL_Rect drecto = {0, 0, 448, 496};
    SDL_Rect pacman_rect = {jogo->pacman->pos_x-4, jogo->pacman->pos_y-4, 24, 24};
    // SDL_Rect teste = {jogo->squares[14][12].x, jogo->squares[14][12].y, 28, 28};
    SDL_RenderCopy(renderer, jogo->mapa, NULL, &drecto);
    SDL_RenderCopy(renderer, jogo->pacman->texture, &jogo->pacman->frames[0], &pacman_rect);
    // SDL_RenderCopy(renderer, jogo->inimigos[0].textura, &jogo->inimigos->frames[0], &teste);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    desenharGhost(jogo->squares, jogo->inimigos, renderer);
    desenhaLinhas(jogo, renderer);
    SDL_RenderPresent(renderer);
}

void stringAux(int direcao, int x, int y, int w, int h, int i, int j, Jogo *jogo)
{
    if (direcao == LEFT)
    {
        cout << "\nWALL\n";
        cout << "LEFT\n";
        cout << "id = ";
        cout << jogo->id_squares[i][j] << " Rects x,y,w,h = ";
        cout << jogo->squares[i][j].x << " ";
        cout << jogo->squares[i][j].y << " ";
        cout << jogo->squares[i][j].w << " ";
        cout << jogo->squares[i][j].h << "\n";
        cout << "x-vel, y+h/2 == " << x-jogo->pacman->velocidade
            << ", " << y+(h/2) << "\n";
        cout << "i, j == " << i << ", " << j << "\n";
        cout << "pacman_x, pacman_y == " << x
            << ", " << 
            y << "\n";
        cout << "prox = " << jogo->prox_move << "\n";
    }
    else if (direcao == RIGHT)
    {
        cout << "\nWALL\n";
        cout << "RIGHT\n";
        cout << "id = ";
        cout << jogo->id_squares[i][j] << " Rects x,y,w,h = ";
        cout << jogo->squares[i][j].x << " ";
        cout << jogo->squares[i][j].y << " ";
        cout << jogo->squares[i][j].w << " ";
        cout << jogo->squares[i][j].h << "\n";
        cout << "x+h+vel, y+h/2 == " << x+h+jogo->pacman->velocidade
            << ", " << y+(h/2) << "\n";
        cout << "i, j == " << i << ", " << j << "\n";
        cout << "pacman_x, pacman_y == " << jogo->pacman->pos_x
            << ", " << 
            jogo->pacman->pos_y << "\n";
        cout << "prox = " << jogo->prox_move << "\n";
    }
    else if (direcao == UP)
    {
        cout << "\nWALL\n";
        cout << "UP\n";
        cout << "id = ";
        cout << jogo->id_squares[i][j] << " Rects x,y,w,h = ";
        cout << jogo->squares[i][j].x << " ";
        cout << jogo->squares[i][j].y << " ";
        cout << jogo->squares[i][j].w << " ";
        cout << jogo->squares[i][j].h << "\n";
        cout << "x+w/2, y-vel == " << x+(w/2)
        << ", " << y-jogo->pacman->velocidade << "\n";
        cout << "i, j == " << i << ", " << j << "\n";
        cout << "pacman_x, pacman_y == " << jogo->pacman->pos_x
            << ", " << 
            jogo->pacman->pos_y << "\n";
        cout << "prox = " << jogo->prox_move << "\n";
    }
    else if (direcao == DOWN)
    {
        cout << "\nWALL\n";
        cout << "DOWN\n";
        cout << "id = ";
        cout << jogo->id_squares[i][j] << " Rects x,y,w,h = ";
        cout << jogo->squares[i][j].x << " ";
        cout << jogo->squares[i][j].y << " ";
        cout << jogo->squares[i][j].w << " ";
        cout << jogo->squares[i][j].h << "\n";
        cout << "x+w/2, y+h+vel == " << x+(w/2)
        << ", " << y+h+jogo->pacman->velocidade << "\n";
        cout << "i, j == " << i << ", " << j << "\n";
        cout << "pacman_x, pacman_y == " << jogo->pacman->pos_x
            << ", " << 
            jogo->pacman->pos_y << "\n";
        cout << "prox = " << jogo->prox_move << "\n";
    }

}

bool colisao2(Jogo *jogo)
{
    for (int i = 0; i < 31; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            int x = jogo->pacman->pos_x;
            int y = jogo->pacman->pos_y;
            int w = 16;
            int h = 16;

            int bx = jogo->squares[i][j].x;
            int by = jogo->squares[i][j].y;
            int bw = 16;
            int bh = 16;

            int vel = jogo->pacman->velocidade;
            int dir = jogo->pacman->direcao;

            // intercepta na coordenada x?
            // down
            if (x < bx+bw && x+w > bx && y+h < by)
            {
                if (jogo->id_squares[i][j] == WALL)
                {
                    stringAux(jogo->pacman->direcao, x, y, w, h, i, j, jogo);
                    return true;
                }
                // else
                // {
                //     return false;
                // }
                
            }
        }
    }
    return false;
}
//

bool colisao(Jogo *jogo)
{
    int x = jogo->pacman->pos_x-4;
    int y = jogo->pacman->pos_y-4;
    int w = 24;
    int h = 24;
    int vel = jogo->pacman->velocidade;

    for (int i = 0; i < 31; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            int centro_x = x+(w/2);
            int centro_y = y+(h/2);
            int bx = jogo->squares[i][j].x;
            int by = jogo->squares[i][j].y;
            int bw = 16;
            int bh = 16;
            

            if(jogo->pacman->direcao == LEFT)
            {
                if (centro_y > by && centro_y < by+bh)
                {
                    if (centro_x > bx && centro_x < bx+bw)
                    {
                        cout << "i, j == " << i << ", " << j << "\n";
                        cout << jogo->id_squares[i][j] << "Rects x,y,w,h = ";
                        cout << jogo->squares[i][j].x << " ";
                        cout << jogo->squares[i][j].y << " ";
                        cout << jogo->squares[i][j].w << " ";
                        cout << jogo->squares[i][j].h << "\n";
                        jogo->pacman->pos_i = i;
                        jogo->pacman->pos_j = j;
                    }
                }
                if (jogo->id_squares[i][j] == WALL)
                {

                    if (y+(h/2) >= jogo->squares[i][j].y
                        && y+(h/2) <= jogo->squares[i][j].h 
                        && x+vel < jogo->squares[i][j].w
                        && x+vel >= jogo->squares[i][j].x)
                    {   
                        stringAux(LEFT, x, y, w, h, i, j, jogo);
                        return true;
                    }
                }
            }
            else if (jogo->pacman->direcao == RIGHT)
            {
                if (centro_y > by && centro_y < by+bh)
                {
                    if (centro_x > bx && centro_x < bx+bw)
                    {
                        cout << "i, j == " << i << ", " << j << "\n";
                        cout << jogo->id_squares[i][j] << "Rects x,y,w,h = ";
                        cout << jogo->squares[i][j].x << " ";
                        cout << jogo->squares[i][j].y << " ";
                        cout << jogo->squares[i][j].w << " ";
                        cout << jogo->squares[i][j].h << "\n";
                        jogo->pacman->pos_i = i;
                        jogo->pacman->pos_j = j;
                    }
                }
                if (jogo->id_squares[i][j] == WALL)
                {
                    if (y+(h/2) >= jogo->squares[i][j].y
                        && y+(h/2) <= jogo->squares[i][j].h 
                        && x+w-vel <= jogo->squares[i][j].w
                        && x+w-vel > jogo->squares[i][j].x)
                    {
                        stringAux(RIGHT, x, y, w, h, i, j, jogo);
                        return true;
                    }
                }
            }
            else if (jogo->pacman->direcao == UP)
            {
                if (centro_y > by && centro_y < by+bh)
                {
                    if (centro_x > bx && centro_x < bx+bw)
                    {
                        cout << "i, j == " << i << ", " << j << "\n";
                        cout << jogo->id_squares[i][j] << "Rects x,y,w,h = ";
                        cout << jogo->squares[i][j].x << " ";
                        cout << jogo->squares[i][j].y << " ";
                        cout << jogo->squares[i][j].w << " ";
                        cout << jogo->squares[i][j].h << "\n";
                        jogo->pacman->pos_i = i;
                        jogo->pacman->pos_j = j;
                    }
                }
                if (jogo->id_squares[i][j] == WALL)
                {
                    if (x+(w/2) >= jogo->squares[i][j].x
                        && x+(w/2) <= jogo->squares[i][j].w 
                        && y < jogo->squares[i][j].h
                        && y >= jogo->squares[i][j].y)
                    {
                        stringAux(UP, x, y, w, h, i, j, jogo);
                        return true;
                    }
                }
            }
            else if (jogo->pacman->direcao == DOWN)
            {
                if (centro_y > by && centro_y < by+bh)
                {
                    if (centro_x > bx && centro_x < bx+bw)
                    {
                        cout << "\ni, j == " << i << ", " << j << "\n";
                        cout << jogo->id_squares[i][j] << "Rects x,y,w,h = ";
                        cout << jogo->squares[i][j].x << " ";
                        cout << jogo->squares[i][j].y << " ";
                        cout << jogo->squares[i][j].w << " ";
                        cout << jogo->squares[i][j].h << "\n";
                        jogo->pacman->pos_i = i;
                        jogo->pacman->pos_j = j;
                    }
                }
                if (jogo->id_squares[i][j] == WALL)
                {
                    if (x+(w/2) >= jogo->squares[i][j].x
                        && x+(w/2) <= jogo->squares[i][j].w 
                        && y+h-vel <= jogo->squares[i][j].h
                        && y+h-vel > jogo->squares[i][j].y)
                    {
                        stringAux(DOWN, x, y, w, h, i, j, jogo);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void eventosJogo(Jogo **jogo, bool &on)
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        switch ((&e)->type)
        {
        case SDL_QUIT:
            on = false;
            break;
        
        case SDL_KEYDOWN:
            switch ((&e)->key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    on = false;
                    break;
            }   
        }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP])
    {
        (*jogo)->pacman->direcao = UP;
        if (!colisao(*jogo))
        {
            (*jogo)->pacman->pos_y -= (*jogo)->pacman->velocidade;
        }
        else
        {
            (*jogo)->pacman->direcao = STOP;
        }
    }
    else if (state[SDL_SCANCODE_DOWN])
    {
        (*jogo)->pacman->direcao = DOWN;
        if (!colisao(*jogo))
        {
            (*jogo)->pacman->pos_y += (*jogo)->pacman->velocidade;
        }
        else
        {
            (*jogo)->pacman->direcao = STOP;
        }
    }
    else if (state[SDL_SCANCODE_LEFT])
    {
        (*jogo)->pacman->direcao = LEFT;
        if (!colisao(*jogo))
        {
            (*jogo)->pacman->pos_x -= (*jogo)->pacman->velocidade;
            if ((*jogo)->pacman->pos_x+24 < (*jogo)->squares[14][0].x)
                (*jogo)->pacman->pos_x = 448;
        }
        else
        {
            (*jogo)->pacman->direcao = STOP;
        }
        
    }
    else if (state[SDL_SCANCODE_RIGHT])
    {
        (*jogo)->pacman->direcao = RIGHT;
        if (!colisao(*jogo))
        {
            (*jogo)->pacman->pos_x += (*jogo)->pacman->velocidade;
            if ((*jogo)->pacman->pos_x > (*jogo)->squares[14][27].w)
                (*jogo)->pacman->pos_x = 0;
        }
        else
        {
            (*jogo)->pacman->direcao = STOP;
        }
    }
}
void movimentosGhost(Jogo **jogo)
{
    Jogo *cpy = *jogo;
    for (int i = 0; i < 4; i++)
    {
        if (cpy->inimigos[i].caminho.empty())
        {
            cout << "\n\nentrou switch\n";
            ii start = make_pair(cpy->inimigos[i].x, cpy->inimigos[i].y);
            int destX = (cpy->pacman->pos_x+12)/16;
            int destY = (cpy->pacman->pos_y+12)/16;

            cout << "dest x,y == " << destX << ", " << destY << "\n";

            // if(abs((*jogo)->inimigos[i].x-destX))
            No inicio = criaInicio(start.first, start.second, destX, destY);
            No fim = criaFim(destX, destY);

            vector<No> lst = A_star(inicio, fim, cpy->id_squares);
            cpy->inimigos[i].caminho = cria_caminho(lst);
        }
        else
        {

        }

        // while (!caminho.empty())
        // {
        //     // No prox = ;
        //     // while ()
        // }
        // cpy->inimigos[i].tipo_mv = 2; 
    }
    // *jogo = cpy;
}
