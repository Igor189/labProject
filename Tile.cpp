#include "Tile.h"
/*Tile::Tile(int x, int y, int tileType)
{
	Collider.x = x;
	Collider.y = y;

	Collider.w = TILE_WIDTH;
	Collider.h = TILE_HEIGHT;

	type = tileType;
}
SDL_Rect Tile::getCollider()
{
	return Collider;
}
int Tile::getType()
{
	return type;
}
void Tile::render(SDL_Rect& camera, SDL_Renderer* Renderer, Texture& tileTexture)
{
	if (checkCollision(camera, Collider))
	{
		//Show the tile
		tileTexture.render(Collider.x - camera.x, Collider.y - camera.y, Renderer, &gTileClips[type]);
	}
}


bool Tile::setTiles(Tile* tiles[])
{
	bool tilesLoaded = true;

	//The tile offsets
	int x = 0, y = 0;

	//Open the map
	ifstream map("map.map");

	//If the map couldn't be loaded
	if (map.fail())
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		//Initialize the tiles
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;

			//If the was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
			{
				tiles[i] = new Tile(x, y, tileType);
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if (x >= LEVEL_WIDTH)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}

		//Clip the sprite sheet
		if (tilesLoaded)
		{
			gTileClips[TILE_GROUND_UP_LEFT].x = 0;
			gTileClips[TILE_GROUND_UP_LEFT].y = 0;
			gTileClips[TILE_GROUND_UP_LEFT].w = TILE_WIDTH;
			gTileClips[TILE_GROUND_UP_LEFT].h = TILE_HEIGHT;

			gTileClips[TILE_GROUND_UP_MID].x = 80;
			gTileClips[TILE_GROUND_UP_MID].y = 0;
			gTileClips[TILE_GROUND_UP_MID].w = TILE_WIDTH;
			gTileClips[TILE_GROUND_UP_MID].h = TILE_HEIGHT;

			gTileClips[TILE_GROUND_UP_RIGHT].x = 160;
			gTileClips[TILE_GROUND_UP_RIGHT].y = 0;
			gTileClips[TILE_GROUND_UP_RIGHT].w = TILE_WIDTH;
			gTileClips[TILE_GROUND_UP_RIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_GROUND_DOWN_LEFT].x = 0;
			gTileClips[TILE_GROUND_DOWN_LEFT].y = 80;
			gTileClips[TILE_GROUND_DOWN_LEFT].w = TILE_WIDTH;
			gTileClips[TILE_GROUND_DOWN_LEFT].h = TILE_HEIGHT;

			gTileClips[TILE_GROUND_DOWN_MID].x = 80;
			gTileClips[TILE_GROUND_DOWN_MID].y = 80;
			gTileClips[TILE_GROUND_DOWN_MID].w = TILE_WIDTH;
			gTileClips[TILE_GROUND_DOWN_MID].h = TILE_HEIGHT;

			gTileClips[TILE_GROUND_DOWN_RIGHT].x = 160;
			gTileClips[TILE_GROUND_DOWN_RIGHT].y = 80;
			gTileClips[TILE_GROUND_DOWN_RIGHT].w = TILE_WIDTH;
			gTileClips[TILE_GROUND_DOWN_RIGHT].h = TILE_HEIGHT;

			gTileClips[TILE_NOTHING].x = 240;
			gTileClips[TILE_NOTHING].y = 0;
			gTileClips[TILE_NOTHING].w = TILE_WIDTH;
			gTileClips[TILE_NOTHING].h = TILE_HEIGHT;
		}
	}

	//Close the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}*/
