#pragma once
#include"movableObject.h"
class Player:public movableObject
{
private:
	const float jumpSpeed;
	SDL_Rect animation[5];
	float animFrame;
	bool changeAnim=false;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
public:
	Player(int x,int y,string imgName,SDL_Renderer* Renderer);
	const int VEL = 120;
	const int PLAYER_HEIGHT = 20;
	const int PLAYER_WIDTH = 20;
	const int WALKING_ANIMATION = 3;
	const int TOTAL_ANIMATION = 5;
	void move(vector<SDL_Rect>& walls,float timeStep);
	void handleEvent(SDL_Event& e, vector<SDL_Rect>& walls);
	SDL_Rect* getAnim(int frame);
	void render(SDL_Renderer* Renderer, SDL_Rect& camera);
	void setCamera(SDL_Rect& camera);
	void teleport(SDL_Rect& teleportCollider);
	void setPos(int x,int y);
};