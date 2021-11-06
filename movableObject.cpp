#include"movableObject.h"


movableObject::movableObject(int x, int y, string imgName, SDL_Renderer* Renderer): Object::Object(x, y, imgName, Renderer)
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
bool movableObject::checkCollision(vector<SDL_Rect>& walls)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = Collider.x;
	rightA = Collider.x + Collider.w;
	topA = Collider.y;
	bottomA = Collider.y + Collider.h;

	for (int i = 0; i < walls.size(); i++)
	{
		//Calculate the sides of rect B
		leftB = walls[i].x;
		rightB = walls[i].x + walls[i].w;
		topB = walls[i].y;
		bottomB = walls[i].y + walls[i].h;
		//If any of the sides from A are outside of B
		if (!((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)))
		{
			//A collision is detected
			return true;
		}
	}
	return false;
}
