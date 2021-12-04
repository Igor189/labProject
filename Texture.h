#pragma once
#include<SDL_image.h>
#include <string>
#include"Function.h"
using namespace std;

class Texture
{
private:
	int width;
	int height;
	SDL_Texture* texture;
public:
	Texture();
	~Texture();
	void free();
	int getWidth();
	int getHeight();
	void render(int x, int y, SDL_Renderer* Renderer, SDL_Rect* renderRect = NULL);
	bool loadFromFile(string fileName, SDL_Renderer* Renderer, bool colorKey=true);
};
