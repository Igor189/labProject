#include "Player.h"
#include<iostream>
#include "Timer.h"
#include"Function.h"
Player::Player(int x, int y, string imgName, SDL_Renderer* Renderer) :movableObject(x, y, imgName, Renderer),jumpSpeed(1000)
{
	animFrame = 0;
	velY = gravity;
	for (int i = 0; i < 5; i++)
	{
		animation[i].h = PLAYER_HEIGHT;
		animation[i].w = PLAYER_WIDTH;
		animation[i].x = i * PLAYER_HEIGHT;
		animation[i].y = 0;
	}
	Collider.h = PLAYER_HEIGHT;
	Collider.w = PLAYER_WIDTH;
}

void Player::move(vector<SDL_Rect>& walls,float timeStep)
{
	posX += velX*timeStep;
	Collider.x = posX;
	if (posX < 0 || posX + PLAYER_WIDTH>SCREEN_WIDTH || checkCollision(walls,Collider))
	{
		posX -=velX*timeStep;
		Collider.x = posX;
	}
	
	posY += velY*timeStep;
	Collider.y = posY;
	if (posY < 0 || posY + PLAYER_HEIGHT>SCREEN_HEIGHT || checkCollision(walls, Collider))
	{
		posY -= velY * timeStep;
		Collider.y = posY;
	}
}
SDL_Rect* Player::getAnim(int frame)
{
	return &animation[frame];
}
void Player::render(SDL_Renderer* Renderer)
{
	objectTexture.render(posX, posY, Renderer, &animation[animFrame]);
}
/*Uint32 callback(Uint32 interval, void* param)
{
	int* frame=static_cast<int*>(param);
	cout << frame;
	//*frame++;
	//cout << frame;
	//if (*frame > 2)
	//	*frame = 0;
	return 0;
}*/
void Player::handleEvent(SDL_Event& e,vector<SDL_Rect>& walls)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			animFrame = 3;
			SDL_Rect onGroundCollider = Collider;
			onGroundCollider.y++;
			if (checkCollision(walls, onGroundCollider))
			{
				posY -= 30;
				Collider.y = posY;
			}
			break;
		case SDLK_LEFT: 
			velX -= VEL; break;
		case SDLK_RIGHT: 
			velX += VEL; break;
		}
	}
	if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: 
			animFrame = 4;
			velY = gravity;break;
		case SDLK_LEFT: 
			velX += VEL; break;
		case SDLK_RIGHT: 
			velX -= VEL; break;
		}
	}
}
void Player::setCamera(SDL_Rect& camera)
{
	//Center the camera over the dot
	camera.x = (Collider.x + PLAYER_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (Collider.y + PLAYER_HEIGHT / 2) - SCREEN_HEIGHT / 2;

	//Keep the camera in bounds
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h)
	{
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}
