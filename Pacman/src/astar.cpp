#include "../includes/astar.hpp"

bool equal(No um, No dois)
{
    return (um.i == dois.i) && (um.j == dois.j);
}

int manhattan(No um, No dois)
{
    return abs(um.i-dois.i) + abs(um.j-dois.j);
}

No criaFim(int i, int j)
{
    No fim;
    No aux;
    fim.i = i; aux.i = i;
    fim.j = j; aux.j = j;
    fim.w = manhattan(fim, aux);
    fim.pai = {-1, -1};
    return fim;
}
No criaInicio(int i, int j, int i_final, int j_final)
{
    No inicio;
    No aux;
    inicio.i = i; aux.i = i_final;
    inicio.j = j; aux.j = j_final;
    inicio.w = manhattan(inicio, aux);
    inicio.pai.first = inicio.i;
    inicio.pai.second = inicio.j;
    // cout << "aaa\n";
    return inicio;
}

No iniciaNo(int i, int j, No inicio, No dest, No pai)
{
    No node;
    node.i = i;
    node.j = j;
    node.w = manhattan(dest, node);
    node.pai.first = pai.i;
    node.pai.second = pai.j;
    return node;
}

void abreNo(No inicio, No dest, No atual, priority_queue<No, vector<No>, decltype(comp)> &fila, vector<No> &pilha, int id_squares[31][28])
{
    // cout << "\n\natual = " << atual.i << " " << atual.j << " " << atual.w << "\n";
    if (atual.i < 30 && id_squares[atual.i+1][atual.j] != WALL || 
        (atual.i+1 == 12 && (atual.j == 13 || atual.j == 14)))
    {
        int achou = 0;
        No aux = iniciaNo(atual.i+1, atual.j, inicio, dest, atual);
        if (!pilha.empty())
        {
            for (auto it = pilha.begin(); it != pilha.end(); it++)
            {
                if (it->i == aux.i && it->j == aux.j)
                {
                    achou = 1;
                }   
            }
        }
        if (achou == 0)
        {
            fila.push(aux);
            // cout << "aux = " << aux.i << " " << aux.j << " " << aux.w << " right\n";
        }
    }
    if (atual.i > 0 && id_squares[atual.i-1][atual.j] != WALL ||
        (atual.i-1 == 12 && (atual.j == 13 || atual.j == 14)))
    {
        int achou = 0;
        No aux = iniciaNo(atual.i-1, atual.j, inicio, dest, atual);
        if (!pilha.empty())
        {
            for (auto it = pilha.begin(); it != pilha.end(); it++)
            {
                if (it->i == aux.i && it->j == aux.j)
                {
                    achou = 1;
                }
            }
        }
        if (achou == 0)
        {
            fila.push(aux);
            // cout << "aux = " << aux.i << " " << aux.j << " " << aux.w << " left\n";
        }
    }
    if (atual.j < 28 && id_squares[atual.i][atual.j+1] != WALL ||
        (atual.i == 12 && (atual.j+1 == 13 || atual.j+1 == 14)))
    {
        int achou = 0;
        No aux = iniciaNo(atual.i, atual.j+1, inicio, dest, atual);
        if (!pilha.empty())
        {
            for (auto it = pilha.begin(); it != pilha.end(); it++)
            {
                if (it->i == aux.i && it->j == aux.j)
                {
                    // cout << "entrou\n";
                    achou = 1;
                }
            }
        }
        if (achou == 0)
        {
            fila.push(aux);
            // cout << "aux = " << aux.i << " " << aux.j << " " << aux.w << " down\n";
        }
    }
    if (atual.j > 0 && id_squares[atual.i][atual.j-1] != WALL || 
        (atual.i == 12 && (atual.j-1 == 13 || atual.j-1 == 14)))
    {
        int achou = 0;
        No aux = iniciaNo(atual.i, atual.j-1, inicio, dest, atual);
        
        if (!pilha.empty())
        {
            for (auto it = pilha.begin(); it != pilha.end(); it++)
            {
                if (it->i == aux.i && it->j == aux.j)
                {
                    achou = 1;
                }
            }
        }
        if (achou == 0)
        {
            fila.push(aux);
            // cout << "aux = " << aux.i << " " << aux.j << " " << aux.w << " up\n";
        }
    }
}

vector<No> A_star(No inicio, No dest, int id_squares[31][28])
{
    priority_queue<No, vector<No>, decltype(comp)> fila(comp);
    vector<No> lst_fechada;
    abreNo(inicio, dest, inicio, fila, lst_fechada, id_squares);
    No atual;
    while (!fila.empty())
    {
        atual = fila.top();
        fila.pop();
        lst_fechada.push_back(atual);
        // cout << "top = " << fila.top().i << " " << fila.top().j << " " << fila.top().w << endl;
        if (equal(atual, dest))
        {
            break;
        }
        abreNo(inicio, dest, atual, fila, lst_fechada, id_squares);
    }
    cout << "\nSAIU TOP = " << fila.top().i << " " << fila.top().j << " " << fila.top().w << endl;
    // for (auto it = lst_fechada.begin(); it != lst_fechada.end(); it++)
    // {
    //     cout << "i,j,w = " << it->i << "," << it->j << "," << it->w << "\n";
    //     cout << "pai i,j = " << it->pai.first << "," << it->pai.second << "\n\n";
    // }
    return lst_fechada;
}
vector<No> cria_caminho(vector<No> &lst_fechada)
{
    vector<No> caminho;
    caminho.push_back(lst_fechada.back());
    ii pai = lst_fechada.back().pai;
    cout << "caminho i, j == " << caminho.back().i << ", " << caminho.back().j << "\n";
    lst_fechada.pop_back();
    while (!lst_fechada.empty())
    {
        if (lst_fechada.back().i == pai.first && lst_fechada.back().j == pai.second)
        {
            caminho.push_back(lst_fechada.back());
            pai = lst_fechada.back().pai;
            cout << "caminho i, j == " << caminho.back().i << ", " << caminho.back().j << "\n";
        }
        lst_fechada.pop_back();
    }
    return caminho;
}