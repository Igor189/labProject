#pragma once
#include"Object.h"
const int TOTAL_TILES = 42 * 19;
class Map
{
private:
	Object* tiles[TOTAL_TILES];
	vector<SDL_Rect> collision;
public:
	const int TILE_WIDTH = 32;
	const int TILE_HEIGHT = 32;
	const int TOTAL_TILE_SPRITES = 60;
	Map(SDL_Renderer* Renderer);
	vector <SDL_Rect>& getCollision();
	void render(SDL_Renderer* Renderer,SDL_Rect& camera);

};