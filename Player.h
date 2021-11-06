#pragma once
#include"movableObject.h"
class Player:public movableObject
{
public:
	Player(int x,int y,string imgName,SDL_Renderer* Renderer);
	static const int VEL = 1;
	static const int PLAYER_HEIGHT = 20;
	static const int PLAYER_WIDTH = 20;
	void move(vector<SDL_Rect>& walls);
	int handleEvent(SDL_Event& e);
};