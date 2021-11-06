#include "Player.h"
#include<iostream>
Player::Player(int x, int y,string imgName,SDL_Renderer* Renderer):movableObject(x,y,imgName,Renderer)
{
}


void Player::move(vector<SDL_Rect>& walls)
{
	posX += velX;
	Collider.x = posX;
	if (posX<0 || posX + PLAYER_WIDTH>SCREEN_WIDTH || checkCollision(walls))
	{
		posX -= velX;
		Collider.x = posX;
	}

	posY += velY;
	Collider.y = posY;
	if (posY<0 || posY + PLAYER_HEIGHT>SCREEN_HEIGHT || checkCollision(walls))
	{
		posY -= velY;
		Collider.y = posY;
	}
}

int Player::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: velY -= VEL; break;
		case SDLK_DOWN: velY += VEL; break;
		case SDLK_LEFT: velX -= VEL; break;
		case SDLK_RIGHT: velX += VEL; break;
		}
	}
	if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: velY += VEL;break;
		case SDLK_DOWN: velY -= VEL; break;
		case SDLK_LEFT: velX += VEL; break;
		case SDLK_RIGHT: velX -= VEL; break;
		}
	}
	return velX;
}
