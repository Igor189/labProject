#include"Function.h"

bool checkCollision(vector<SDL_Rect>& walls, SDL_Rect Collider)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = Collider.x;
	rightA = Collider.x + Collider.w;
	topA = Collider.y;
	bottomA = Collider.y + Collider.h;

	for (int i = 0; i < walls.size(); i++)
	{
		leftB = walls[i].x;
		rightB = walls[i].x + walls[i].w;
		topB = walls[i].y;
		bottomB = walls[i].y + walls[i].h;

		if (!((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)))
		{
			return true;
		}
	}
	return false;
}

bool checkCollision(SDL_Rect walls, SDL_Rect Collider)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = Collider.x;
	rightA = Collider.x + Collider.w;
	topA = Collider.y;
	bottomA = Collider.y + Collider.h;

	leftB = walls.x;
	rightB = walls.x + walls.w;
	topB = walls.y;
	bottomB = walls.y + walls.h;
	
	if (!((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)))
	{
		return true;
	}
return false;
}
