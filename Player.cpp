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
	if (changeAnim)
		animFrame += timeStep*3;
	if (animFrame > 2.5&&changeAnim)
		animFrame = 0;
	posX += velX*timeStep;
	Collider.x = posX;
	if (posX < 0 || posX + PLAYER_WIDTH>LEVEL_WIDTH || checkCollision(walls,Collider))
	{
		posX -=velX*timeStep;
		Collider.x = posX;
	}
	
	posY += velY*timeStep;
	Collider.y = posY;
	if (posY < 0 || posY + PLAYER_HEIGHT>LEVEL_HEIGHT || checkCollision(walls, Collider))
	{
		posY -= velY * timeStep;
		Collider.y = posY;
	}
}
SDL_Rect* Player::getAnim(int frame)
{
	return &animation[frame];
}
void Player::render(SDL_Renderer* Renderer,SDL_Rect& camera )
{
	objectTexture.render(posX-camera.x, posY-camera.y, Renderer, &animation[(int)animFrame],0.0,NULL,flip);
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
			//changeAnim = false;
			SDL_Rect onGroundCollider = Collider;
			onGroundCollider.y++;
			if (checkCollision(walls, onGroundCollider))
			{
				posY -= 30;
				Collider.y = posY;
				if (checkCollision(walls, Collider))
				{
					posY += 30;
					Collider.y = posY;
				}
			}
			break;
		case SDLK_LEFT: 
			changeAnim = true;
			flip = SDL_FLIP_HORIZONTAL;
			velX -= VEL; break;
		case SDLK_RIGHT: 
			flip = SDL_FLIP_NONE;
			changeAnim = true;
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
			changeAnim = false;
			velX += VEL; break;
		case SDLK_RIGHT: 
			changeAnim = false;
			velX -= VEL; break;
		}
	}
}
void Player::setCamera(SDL_Rect& camera)
{
	camera.x = (Collider.x + PLAYER_WIDTH / 2) - SCREEN_WIDTH / 2;
	camera.y = (Collider.y + PLAYER_HEIGHT / 2) - SCREEN_HEIGHT / 2;

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

void Player::teleport(SDL_Rect& teleportCollider)
{
	if (checkCollision(teleportCollider, Collider))
	{
		posX = 646;
		posY = 204;
		Collider.x = posX;
		Collider.y = posY;
	}
}

void Player::setPos(int x, int y)
{
	posX = x;
	posY = y;
	Collider.x = x;
	Collider.y = y;
	velX = 0;
	velY = gravity;
}


