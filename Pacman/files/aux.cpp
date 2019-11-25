#include "../includes/aux.hpp"
#include <cstring>

bool write_texture()
{
    string arquivo;
    char path[100];
    string entrada;
    string aux;
    string delimiter = "x";
    ii size;
    int w, h;

    cout << "Digite o nome do binario: ";
    cin >> arquivo;
    cout << "Digite o nome da imagem: ";
    cin >> aux;
    strcpy(path, "./pacman_images/");
    strcat(path, aux.c_str());
    arquivo = "./info/" + arquivo;
    cout << "\nDigite o tamanho da textura (formato w h): ";
    cin >> w >> h;

    FILE *file;
    if ((file = fopen(arquivo.c_str(), "wb")) == NULL)
    {
        cout << "Nao foi possível escrever a textura em " << arquivo << "\n";
        return false;
    }
    fwrite(&w, sizeof(int), 1, file);
    fwrite(&h, sizeof(int), 1, file);
    fwrite(path, sizeof(char), sizeof(path), file);
    // cout << size.first << "\n" << size.second << "\n";
    fclose(file);
    return true;
}
bool write_binary(int type)
{
    // this function will have the switch
    switch(type)
    {
        case TEXTURE:
        {
            write_texture();
        }
    }
    return true;
}

void read_texture()
{
    char path[100];
    string arquivo;
    cout << "Digite o nome do binario da textura: ";
    cin >> arquivo;
    arquivo = "./info/" + arquivo;

    FILE *file;
    if ((file = fopen(arquivo.c_str(), "rb")) == NULL)
    {
        cout << "Nao foi possível escrever a textura em " << arquivo << "\n";
    }
    else
    {
        int w, h;
        fread(&w, sizeof(int), 1, file);
        fread(&h, sizeof(int), 1, file);
        fread(path, sizeof(char), sizeof(path), file);
        cout << path << " " << w << " " << h << "\n";
    }
    fclose(file);
}

void read_binary(int type)
{
    switch (type)
    {
    case TEXTURE:
        break;
    
    default:
        break;
    }
}
int main()
{
    int n;
    cout << "Digite o numero de operações: ";
    cin >> n;
    for (int i=0; i < n; i++)
    {
        cout << "Digite o que quer fazer: "
        << "\n1- Escrever"
        << "\n2- Ler\n";

    }
    write_texture();
    read_texture();
    return 0;
}