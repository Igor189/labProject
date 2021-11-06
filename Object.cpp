#include"Object.h"

Object::Object(int x, int y, string imgName, SDL_Renderer* Renderer)
{
	posX = x;
	posY = y;
	Collider.x = posX;
	Collider.y = posY;
	objectTexture.loadFromFile(imgName, Renderer);
	if (objectTexture.getHeight()+y <= SCREEN_HEIGHT)
		Collider.h = objectTexture.getHeight();
	else
		Collider.h = SCREEN_HEIGHT-y;
	if (objectTexture.getWidth() <= SCREEN_WIDTH)
		Collider.w = objectTexture.getWidth();
	else
		Collider.w = SCREEN_WIDTH;
}


void Object::render(SDL_Renderer* Renderer,SDL_Rect* rect)
{
	objectTexture.render(posX, posY, Renderer,rect);
}

int Object::getX()
{
	return posX;
}

int Object::getY()
{
	return posY;
}

SDL_Rect Object::getCollider()
{
	return Collider;
}
