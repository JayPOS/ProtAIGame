#ifndef ASTAR_HPP
#define ASTAR_HPP

#include "includes.hpp"

typedef struct nos No;
struct nos
{
    int i, j, w;
    ii pai;
};

bool equal(No um, No dois);

auto comp = [](No &um, No &dois) { return um.w > dois.w; };

No criaInicio(int i, int j, int i_final, int j_final);
No criaFim(int i, int j);
No iniciaNo(int i, int j, No inicio, No dest, No pai);

int manhattan(No um, No dois);
// abre no e insere na fila os vizinhos
void abreNo(No inicio, No dest, No atual, priority_queue<No, vector<No>, decltype(comp)> &fila, vector<No> &pilha, int id_squares[31][28]);
vector<No> A_star(No inicio, No dest, int id_squares[31][28]); // retorna lista fechada;
vector<No> cria_caminho(vector<No> &lst_fechada); // cria pilha de caminho pela lst_fechada.

#endif