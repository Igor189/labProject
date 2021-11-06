#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include <string>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
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
	bool loadFromFile(string fileName, SDL_Renderer* Renderer);
};