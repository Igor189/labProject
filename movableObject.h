#pragma once
#include "Object.h"
#include<vector>
class movableObject :public Object
{
protected:
	float velX, velY;
public:
	movableObject(int x, int y, string imgName, SDL_Renderer* Renderer);
	void move();
	int getVelX();
	bool checkCollision(vector<SDL_Rect>& walls);
};