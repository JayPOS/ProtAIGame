#ifndef _H_INCLUDES
#define _H_INCLUDES

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2//SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "sdl_functions.hpp"
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdlib>

const int WALL = 0;
const int FOOD = 1;
const int STREET = 2;
const int BIG_FOOD = 3;
const int PACMAN = 4;
const int GHOST = 5;

const int LEFT = -1;
const int RIGHT = 1;
const int UP = -2;
const int DOWN = 2;
const int STOP = 0;

using namespace std;
using ii = pair<int, int>;

#endif