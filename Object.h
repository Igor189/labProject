#pragma once
#include"Texture.h"

class Object
{
protected:
	float posX, posY;
	SDL_Rect Collider;
	Texture objectTexture;
public:

	Object(int x, int y, string imgName, SDL_Renderer* Renderer);
	void render(SDL_Renderer* Renderer,SDL_Rect* rect=NULL);
	int getX();
	int getY();
	SDL_Rect getCollider();
};