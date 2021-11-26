#pragma once
#include "Object.h"
class movableObject :public Object
{
protected:
	float velX, velY;
	const float gravity;
public:
	movableObject(int x, int y, string imgName, SDL_Renderer* Renderer);
	void move();
	int getVelX();
};