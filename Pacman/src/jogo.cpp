#include "../includes/jogo.hpp"

ii center(int x, int y, int w, int h)
{
    return make_pair(x+(w/2), y+(h/2));
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
    surface = NULL;
    
    jogo->pacman = carregaPacman(jogo->pacman, renderer);
    jogo->nivel = 1;
    jogo->prox_move = 0;


    jogo->comidas = (SDL_Texture **)malloc(sizeof(SDL_Texture*)*2);
    surface = IMG_Load("./pacman_images/comida-pequena.png");
    if (surface != NULL)
    {
        jogo->comidas[0] = NULL;
        jogo->comidas[0] = SDL_CreateTextureFromSurface(renderer, surface);
        if (jogo->comidas[0] == NULL)
        {
            cout << "Erro na textura comida-pequena\n";
            exit(1);
        }
    }
    else
    {
        cout << "Erro na surface comida-pequena\n";
        exit(1);
    }
    SDL_FreeSurface(surface);
    surface = NULL;

    surface = IMG_Load("./pacman_images/grande.png");
    if (surface != NULL)
    {
        jogo->comidas[1] =  NULL;
        jogo->comidas[1] = SDL_CreateTextureFromSurface(renderer, surface);
        if (jogo->comidas[1] == NULL)
        {
            cout << "Erro na textura comida grande\n";
            exit(1);
        }
    }
    else
    {
        cout << "Erro na surface comida-grande\n";
        exit(1);
    }

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
        jogo->inimigos[i].i = 14; 
        jogo->inimigos[i].j = 12; 
        jogo->inimigos[i].x = jogo->squares[jogo->inimigos[i].i][jogo->inimigos[i].j].x-4;
        jogo->inimigos[i].y = jogo->squares[jogo->inimigos[i].i][jogo->inimigos[i].j].y-4;
        jogo->inimigos[i].prox = new No;
    }

    fclose(file);

    return jogo;
}

void desenhaComidas(SDL_Rect sqr[][28], SDL_Texture **comidas, SDL_Renderer *renderer, int id_sqr[][28])
{
    for (int i = 0; i < 31; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            if (id_sqr[i][j] == FOOD)
            {
                SDL_Rect aux = {sqr[i][j].x, sqr[i][j].y, 16, 16};
                SDL_RenderCopy(renderer, comidas[0], NULL, &aux);
            }
            else if (id_sqr[i][j] == BIG_FOOD)
            {
                SDL_Rect aux = {sqr[i][j].x, sqr[i][j].y, 16, 16};
                SDL_RenderCopy(renderer, comidas[1], NULL, &aux);
            }
        }
    }
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
        SDL_Rect aux = {fant[i].x, fant[i].y, 24, 24};
        SDL_RenderCopy(renderer, fant[0].textura, &fant[i].frames[0], &aux);
    }
}

void desenharJogo(Jogo *jogo, SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
    SDL_Rect drecto = {0, 0, 448, 496};
    SDL_Rect pacman_rect = {jogo->pacman->pos_x-4, jogo->pacman->pos_y-4, 24, 24};
    // SDL_Rect teste = {jogo->squares[14][12].x, jogo->squares[14][12].y, 28, 28};
    SDL_RenderCopy(renderer, jogo->mapa, NULL, &drecto);

    desenhaComidas(jogo->squares, jogo->comidas, renderer, jogo->id_squares);
    SDL_RenderCopy(renderer, jogo->pacman->texture, &jogo->pacman->frames[0], &pacman_rect);

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
                        if (jogo->id_squares[jogo->pacman->pos_i][jogo->pacman->pos_j] == FOOD ||
                            jogo->id_squares[jogo->pacman->pos_i][jogo->pacman->pos_j] == BIG_FOOD)
                            {
                                jogo->id_squares[jogo->pacman->pos_i][jogo->pacman->pos_j] = STREET;
                            }
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
                        if (jogo->id_squares[jogo->pacman->pos_i][jogo->pacman->pos_j] == FOOD ||
                        jogo->id_squares[jogo->pacman->pos_i][jogo->pacman->pos_j] == BIG_FOOD)
                        {
                            jogo->id_squares[jogo->pacman->pos_i][jogo->pacman->pos_j] = STREET;
                        }
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
                        if (jogo->id_squares[jogo->pacman->pos_i][jogo->pacman->pos_j] == FOOD ||
                        jogo->id_squares[jogo->pacman->pos_i][jogo->pacman->pos_j] == BIG_FOOD)
                        {
                            jogo->id_squares[jogo->pacman->pos_i][jogo->pacman->pos_j] = STREET;
                        }
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
                        if (jogo->id_squares[jogo->pacman->pos_i][jogo->pacman->pos_j] == FOOD ||
                        jogo->id_squares[jogo->pacman->pos_i][jogo->pacman->pos_j] == BIG_FOOD)
                        {
                            jogo->id_squares[jogo->pacman->pos_i][jogo->pacman->pos_j] = STREET;
                        }
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

// MOVIMENTOS FANTASMAS

ii destPinky(int pac_i, int pac_j, int direcao, int id_sqr[][28])
{
    ii dest = make_pair(pac_i, pac_j);
    int previsao = 4;
    if (direcao == UP)
    {
        if (pac_i-previsao > 0)
        {
            dest.first -= previsao;
            return dest;
        }
        else
        {
            previsao -= pac_i;
            dest.first -= pac_i;
            if (previsao > 0)
            {
                if (pac_j-previsao > 0)
                {
                    dest.second -= previsao;
                    return dest;
                }
                else
                {
                    dest.second = 0;
                    return dest;
                }
            }
        }
    }
    else if (direcao == DOWN)
    {
        if (pac_i+previsao < 31)
        {
            dest.first += previsao;
            return dest;
        }
        else
        {
            previsao -= pac_i+previsao-31;
            dest.first += previsao;
            if (previsao > 0)
            {
                if (pac_j-previsao > 0)
                {
                    dest.second -= previsao;
                    return dest;
                }
                else
                {
                    dest.second = 0;
                    return dest;
                }
            }
        }
    }
    else if (direcao == LEFT)
    {
        if (pac_j-previsao > 0)
        {
            dest.second -= previsao;
            return dest;
        }
        else
        {
            previsao -= pac_j;
            dest.second -= pac_j;
            if (previsao > 0)
            {
                if (pac_i-previsao > 0)
                {
                    dest.first -= previsao;
                    return dest;
                }
                else
                {
                    dest.first = 0;
                    return dest;
                }
            }
        }
    }
    else if (direcao == RIGHT)
    {
        if (pac_j+previsao < 31)
        {
            dest.second += previsao;
            return dest;
        }
        else
        {
            previsao -= pac_i+previsao-31;
            dest.second += previsao;
            if (previsao > 0)
            {
                if (pac_i-previsao > 0)
                {
                    dest.first -= previsao;
                    return dest;
                }
                else
                {
                    dest.first = 0;
                    return dest;
                }
            }
        }
    }
}

Jogo *chase(Jogo *jogo, int id)
{
    // cout << "blinky x,y == " << jogo->inimigos[BLINKY].x << ", " << jogo->inimigos[BLINKY].y << "\n";
    switch(id)
    {
        case BLINKY:
        {
            int destX = (jogo->pacman->pos_y+12)/16;
            int destY = (jogo->pacman->pos_x+12)/16;
            if (jogo->inimigos[BLINKY].caminho.empty())
            {
                // cout << "\n\nentrou switch\n";
                ii start = make_pair(jogo->inimigos[BLINKY].i, jogo->inimigos[BLINKY].j);
                

                // cout << "dest x,y == " << destX << ", " << destY << "\n";

                // if(abs((*jogo)->inimigos[i].x-destX))
                No inicio = criaInicio(start.first, start.second, destX, destY);
                *jogo->inimigos[BLINKY].prox = inicio;
                No fim = criaFim(destX, destY);

                vector<No> lst = A_star(inicio, fim, jogo->id_squares);
                jogo->inimigos[BLINKY].caminho = cria_caminho(lst);
                
                *jogo->inimigos[BLINKY].prox = jogo->inimigos[BLINKY].caminho.back();
            }
            else
            {
                ii prox_centro = center(jogo->squares[jogo->inimigos[BLINKY].i][jogo->inimigos[BLINKY].j].x, 
                                                    jogo->squares[jogo->inimigos[BLINKY].i][jogo->inimigos[BLINKY].j].y,
                                                    16, 
                                                    16);

                jogo->inimigos[BLINKY].centro = center(jogo->inimigos[BLINKY].x,
                                                        jogo->inimigos[BLINKY].y, 
                                                        24,
                                                        24);

                
                if (prox_centro.first == jogo->inimigos[BLINKY].centro.first &&
                                                prox_centro.second == jogo->inimigos[BLINKY].centro.second)

                {
                    // cout << "Entrou centros iguais\n";
                    *jogo->inimigos[BLINKY].prox = jogo->inimigos[BLINKY].caminho.back();
                    jogo->inimigos[BLINKY].i = jogo->inimigos[BLINKY].prox->i;
                    jogo->inimigos[BLINKY].j = jogo->inimigos[BLINKY].prox->j;
                    jogo->inimigos[BLINKY].caminho.pop_back();
                    
                }
                else
                {
                    // cout << "Entrou centros dif\n";
                    // LEFT                                                                                
                    if (jogo->inimigos[BLINKY].centro.first > prox_centro.first &&
                                                            jogo->inimigos[BLINKY].centro.second == prox_centro.second)
                    {
                        // cout << "Entrou left\n";
                        jogo->inimigos[BLINKY].x -= jogo->inimigos[BLINKY].vel;
                        

                    }
                    // RIGHT
                    else if (jogo->inimigos[BLINKY].centro.first < prox_centro.first &&
                                                            jogo->inimigos[BLINKY].centro.second == prox_centro.second)
                    {
                        // cout << "Entrou right\n";
                        jogo->inimigos[BLINKY].x += jogo->inimigos[BLINKY].vel;
                        
                    }
                    // UP
                    else if (jogo->inimigos[BLINKY].centro.first == prox_centro.first &&
                                                            jogo->inimigos[BLINKY].centro.second > prox_centro.second)
                    {
                        // cout << "Entrou up\n";
                        jogo->inimigos[BLINKY].y -= jogo->inimigos[BLINKY].vel;
                    }
                    // DOWN
                    else if (jogo->inimigos[BLINKY].centro.first == prox_centro.first &&
                                                            jogo->inimigos[BLINKY].centro.second < prox_centro.second)
                    {
                        // cout << "Entrou down\n";
                        jogo->inimigos[BLINKY].y += jogo->inimigos[BLINKY].vel;
                       
                    }
                }
                
            }
            
            break;
        }
        case PINKY:
        {
            int destX = (jogo->pacman->pos_y+12)/16;
            int destY = (jogo->pacman->pos_x+12)/16;

            ii destControl = destPinky(destX, destY, jogo->pacman->direcao, jogo->id_squares);
            destX = destControl.first;
            destY = destControl.second;

            if (jogo->inimigos[PINKY].caminho.empty())
            {
                cout << "\n\nentrou switch\n";
                ii start = make_pair(jogo->inimigos[PINKY].i, jogo->inimigos[PINKY].j);
                

                cout << "dest x,y == " << destX << ", " << destY << "\n";

                // if(abs((*jogo)->inimigos[i].x-destX))
                No inicio = criaInicio(start.first, start.second, destX, destY);
                *jogo->inimigos[PINKY].prox = inicio;
                No fim = criaFim(destX, destY);

                vector<No> lst = A_star(inicio, fim, jogo->id_squares);
                jogo->inimigos[PINKY].caminho = cria_caminho(lst);
                
                *jogo->inimigos[PINKY].prox = jogo->inimigos[PINKY].caminho.back();
            }
            else
            {
                ii prox_centro = center(jogo->squares[jogo->inimigos[PINKY].i][jogo->inimigos[PINKY].j].x, 
                                                    jogo->squares[jogo->inimigos[PINKY].i][jogo->inimigos[PINKY].j].y,
                                                    16, 
                                                    16);

                jogo->inimigos[PINKY].centro = center(jogo->inimigos[PINKY].x,
                                                        jogo->inimigos[PINKY].y, 
                                                        24,
                                                        24);

                
                if (prox_centro.first == jogo->inimigos[PINKY].centro.first &&
                                                prox_centro.second == jogo->inimigos[PINKY].centro.second)

                {
                    // cout << "Entrou centros iguais\n";
                    *jogo->inimigos[PINKY].prox = jogo->inimigos[PINKY].caminho.back();
                    jogo->inimigos[PINKY].i = jogo->inimigos[PINKY].prox->i;
                    jogo->inimigos[PINKY].j = jogo->inimigos[PINKY].prox->j;
                    jogo->inimigos[PINKY].caminho.pop_back();
                    
                }
                else
                {
                    // cout << "Entrou centros dif\n";
                    // LEFT                                                                                
                    if (jogo->inimigos[PINKY].centro.first > prox_centro.first &&
                                                            jogo->inimigos[PINKY].centro.second == prox_centro.second)
                    {
                        // cout << "Entrou left\n";
                        jogo->inimigos[PINKY].x -= jogo->inimigos[PINKY].vel;
                        

                    }
                    // RIGHT
                    else if (jogo->inimigos[PINKY].centro.first < prox_centro.first &&
                                                            jogo->inimigos[PINKY].centro.second == prox_centro.second)
                    {
                        // cout << "Entrou right\n";
                        jogo->inimigos[PINKY].x += jogo->inimigos[PINKY].vel;
                        
                    }
                    // UP
                    else if (jogo->inimigos[PINKY].centro.first == prox_centro.first &&
                                                            jogo->inimigos[PINKY].centro.second > prox_centro.second)
                    {
                        // cout << "Entrou up\n";
                        jogo->inimigos[PINKY].y -= jogo->inimigos[PINKY].vel;
                       
                    }
                    // DOWN
                    else if (jogo->inimigos[PINKY].centro.first == prox_centro.first &&
                                                            jogo->inimigos[PINKY].centro.second < prox_centro.second)
                    {
                        cout << "Entrou down\n";
                        jogo->inimigos[PINKY].y += jogo->inimigos[PINKY].vel;
                       
                    }
                    cout << "\n\nprox center x,y == " << prox_centro.first << ", " << prox_centro.second << "\n";
                    cout << "prox center ghost x,y == " << jogo->inimigos[PINKY].centro.first << 
                            ", " << 
                            jogo->inimigos[PINKY].centro.second << "\n";
                    
                    // cout << "pac ghost: " << jogo->pacman->pos_i << ", " << jogo->pacman->pos_j << "\n";
                }
                
            }
            break;
        }
        case INKY:
        {
            int destX = (jogo->pacman->pos_y+12)/16;
            int destY = (jogo->pacman->pos_x+12)/16;
            if (jogo->inimigos[INKY].caminho.empty())
            {
                // cout << "\n\nentrou switch\n";
                ii start = make_pair(jogo->inimigos[INKY].i, jogo->inimigos[INKY].j);
                

                // cout << "dest x,y == " << destX << ", " << destY << "\n";

                // if(abs((*jogo)->inimigos[i].x-destX))
                No inicio = criaInicio(start.first, start.second, destX, destY);
                *jogo->inimigos[INKY].prox = inicio;
                No fim = criaFim(destX, destY);

                vector<No> lst = A_star(inicio, fim, jogo->id_squares);
                jogo->inimigos[INKY].caminho = cria_caminho(lst);
                
                *jogo->inimigos[INKY].prox = jogo->inimigos[INKY].caminho.back();
            }
            else
            {
                ii prox_centro = center(jogo->squares[jogo->inimigos[INKY].i][jogo->inimigos[INKY].j].x, 
                                                    jogo->squares[jogo->inimigos[INKY].i][jogo->inimigos[INKY].j].y,
                                                    16, 
                                                    16);

                jogo->inimigos[INKY].centro = center(jogo->inimigos[INKY].x,
                                                        jogo->inimigos[INKY].y, 
                                                        24,
                                                        24);

                
                if (prox_centro.first == jogo->inimigos[INKY].centro.first &&
                                                prox_centro.second == jogo->inimigos[INKY].centro.second)

                {
                    // cout << "Entrou centros iguais\n";
                    *jogo->inimigos[INKY].prox = jogo->inimigos[INKY].caminho.back();
                    jogo->inimigos[INKY].i = jogo->inimigos[INKY].prox->i;
                    jogo->inimigos[INKY].j = jogo->inimigos[INKY].prox->j;
                    jogo->inimigos[INKY].caminho.pop_back();
                    
                }
                else
                {
                    // cout << "Entrou centros dif\n";
                    // LEFT                                                                                
                    if (jogo->inimigos[INKY].centro.first > prox_centro.first &&
                                                            jogo->inimigos[INKY].centro.second == prox_centro.second)
                    {
                        // cout << "Entrou left\n";
                        jogo->inimigos[INKY].x -= jogo->inimigos[INKY].vel;
                        // if (prox_centro.first == jogo->inimigos[INKY].centro.first &&
                        //                         prox_centro.second == jogo->inimigos[INKY].centro.second)
                        // {
                        //     jogo->inimigos[INKY].i = jogo->inimigos[INKY].prox->i;
                        //     jogo->inimigos[INKY].j = jogo->inimigos[INKY].prox->j;
                        // }

                    }
                    // RIGHT
                    else if (jogo->inimigos[INKY].centro.first < prox_centro.first &&
                                                            jogo->inimigos[INKY].centro.second == prox_centro.second)
                    {
                        // cout << "Entrou right\n";
                        jogo->inimigos[INKY].x += jogo->inimigos[INKY].vel;
                        // if (prox_centro.first == jogo->inimigos[INKY].centro.first &&
                        //                         prox_centro.second == jogo->inimigos[INKY].centro.second)
                        // {
                        //     jogo->inimigos[INKY].i = jogo->inimigos[INKY].prox->i;
                        //     jogo->inimigos[INKY].j = jogo->inimigos[INKY].prox->j;
                        // }
                    }
                    // UP
                    else if (jogo->inimigos[INKY].centro.first == prox_centro.first &&
                                                            jogo->inimigos[INKY].centro.second > prox_centro.second)
                    {
                        // cout << "Entrou up\n";
                        jogo->inimigos[INKY].y -= jogo->inimigos[INKY].vel;
                        // if (prox_centro.first == jogo->inimigos[INKY].centro.first &&
                        //                         prox_centro.second == jogo->inimigos[INKY].centro.second)
                        // {
                        //     jogo->inimigos[INKY].i = jogo->inimigos[INKY].prox->i;
                        //     jogo->inimigos[INKY].j = jogo->inimigos[INKY].prox->j;
                        // }
                    }
                    // DOWN
                    else if (jogo->inimigos[INKY].centro.first == prox_centro.first &&
                                                            jogo->inimigos[INKY].centro.second < prox_centro.second)
                    {
                        // cout << "Entrou down\n";
                        jogo->inimigos[INKY].y += jogo->inimigos[INKY].vel;
                       
                    }
                    // cout << "\n\nprox center x,y == " << prox_centro.first << ", " << prox_centro.second << "\n";
                    // cout << "prox center ghost x,y == " << jogo->inimigos[INKY].centro.first << 
                    //         ", " << 
                    //         jogo->inimigos[INKY].centro.second << "\n";
                    
                    // cout << "pac ghost: " << jogo->pacman->pos_i << ", " << jogo->pacman->pos_j << "\n";
                }
                
            }
            break;
        }
        case CLYDE:
        {
            break;
        }
    }

    return jogo;
}
Jogo * movimentosGhost(Jogo *jogo)
{
    jogo = chase(jogo, BLINKY);
    jogo = chase(jogo, PINKY);
    return jogo;
}

void terminaJogo(Jogo *jogo)
{
    SDL_DestroyTexture(jogo->mapa);
    SDL_DestroyTexture(jogo->pacman->texture);
    for (int i = 0; i < 4; i++)
    {
        SDL_DestroyTexture(jogo->inimigos[i].textura);
        delete[] jogo->inimigos[i].prox;
    }
    SDL_DestroyTexture(jogo->comidas[0]);
    SDL_DestroyTexture(jogo->comidas[1]);
    free(jogo->comidas);
    delete[] jogo->pacman->frames;
    SDL_DestroyTexture(jogo->mapa);
}