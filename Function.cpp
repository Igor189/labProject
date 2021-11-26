#include"Function.h"

bool checkCollision(vector<SDL_Rect>& walls, SDL_Rect Collider)
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

bool checkCollision(SDL_Rect walls, SDL_Rect& Collider)
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

	//Calculate the sides of rect B
	leftB = walls.x;
	rightB = walls.x + walls.w;
	topB = walls.y;
	bottomB = walls.y + walls.h;
	//If any of the sides from A are outside of B
	if (!((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)))
	{
		//A collision is detected
		return true;
	}
return false;
}
