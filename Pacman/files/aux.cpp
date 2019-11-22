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
    strcpy(path, "/home/jorge/JayP_Programs/ProtAIGame/Pacman/pacman_images/");
    strcat(path, aux.c_str());
    arquivo = "/home/jorge/JayP_Programs/ProtAIGame/Pacman/info/" + arquivo;
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
    // fwrite(path, sizeof(char), sizeof(path), file);
    // cout << size.first << "\n" << size.second << "\n";
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

void read_binary()
{
    char path[100];
    string arquivo;
    cout << "Digite o nome do binario da textura: ";
    cin >> arquivo;
    arquivo = "/home/jorge/JayP_Programs/ProtAIGame/Pacman/info/" + arquivo;

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
        // fread(path, sizeof(char), sizeof(path), file);
        cout << " " << w << " " << h << "\n";
    }
    
}

bool read_binary(int type)
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
    // int n;
    // cin >> n;
    // for (int i=0; i < n; i++)
    // {
    //     // Now you write whatever you need
    //     // switch and control variable?
    // }
    write_texture();
    read_binary();
    return 0;
}