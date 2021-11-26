#pragma once
#include<SDL.h>
#include<vector>
using namespace std;
const int LEVEL_WIDTH = 1980;
const int LEVEL_HEIGHT = 1200;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
bool checkCollision(vector<SDL_Rect>& walls, SDL_Rect Collider);
bool checkCollision(SDL_Rect walls, SDL_Rect Collider);