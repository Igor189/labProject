#pragma once
#include"Texture.h"
class Particle
{
private:
	float posX, posY;
	int frame;
	Texture texture;
public:
	Particle(int x,int y);
	void render();
	bool isDead();
};