#include"Object.h"

Object::Object(int x, int y, string imgName, SDL_Renderer* Renderer, bool colorKey)
{
	posX = x;
	posY = y;
	Collider.x = posX;
	Collider.y = posY;
	objectTexture.loadFromFile(imgName, Renderer,colorKey);
	if (objectTexture.getHeight()+y <= LEVEL_HEIGHT)
		Collider.h = objectTexture.getHeight();
	else
		Collider.h = LEVEL_HEIGHT-y;
	if (objectTexture.getWidth() <= LEVEL_WIDTH)
		Collider.w = objectTexture.getWidth();
	else
		Collider.w = LEVEL_WIDTH;
}


void Object::render(SDL_Renderer* Renderer,SDL_Rect& camera,SDL_Rect* rect)
{
	objectTexture.render(posX-camera.x, posY-camera.y, Renderer);
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

void Object::setCollider(int h, int w)
{
	Collider.h = h;
	Collider.w = w;
}

