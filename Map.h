#pragma once
#include"Object.h"
const int TOTAL_TILES = 42 * 19;
class Map
{
private:
	Object* tiles[TOTAL_TILES];
	vector<SDL_Rect> collision;
	vector<SDL_Rect> enemiesCollision;
	SDL_Rect finishCollision;
	SDL_Rect teleport;
public:
	const int TILE_WIDTH = 32;
	const int TILE_HEIGHT = 32;
	const int TOTAL_TILE_SPRITES = 73;
	Map(SDL_Renderer* Renderer);
	vector <SDL_Rect>& getCollision();
	vector<SDL_Rect>& getEnemiesCollision();
	void render(SDL_Renderer* Renderer,SDL_Rect& camera);
	SDL_Rect& getTeleport();
	SDL_Rect& getFinish();
	//void addEnemies(SDL_Renderer* Renderer);
};