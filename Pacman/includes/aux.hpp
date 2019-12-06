#ifndef AUX_HPP
#define AUX_HPP

#include <iostream>
#include <utility>
#include <string>

const int TEXTURE = 1;
const int CLASS = 2;
const int FASE = 3;

using namespace std;
using ii=pair<int, int>;

bool write_texture();
bool write_binary(int type);
void read_texture();
void read_binary();

#endif