#include"movableObject.h"


movableObject::movableObject(int x, int y, string imgName, SDL_Renderer* Renderer): Object::Object(x, y, imgName, Renderer),gravity(40)
{
	velX = 0;
	velY = 0;
}

void movableObject::move()
{
	posX += velX;
	if (posX<0 || posX + Collider.w>SCREEN_WIDTH)
	{
		posX -= velX;
	}

	posY += velY;
	if (posY<0 || posY + Collider.h>SCREEN_HEIGHT)
	{
		posY -= velY;
	}
}

int movableObject::getVelX()
{
	return velX;
}