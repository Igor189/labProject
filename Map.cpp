#include"Map.h"
#include<fstream>
#include<sstream>
Map::Map(SDL_Renderer* Renderer)
{
	bool tilesLoaded = true;
	string tile = "Tiles/Tile_";
	string png = ".png";
	string zero = "0";
	int x = 0, y = 0;

	ifstream map("map.map");

	if (map.fail())
	{
		printf("Unable to load map file!\n");
		tilesLoaded = false;
	}
	else
	{
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			int tileType = -1;

			map >> tileType;

			if (map.fail())
			{
				printf("Error loading map: Unexpected end of file!\n");
				tilesLoaded = false;
				break;
			}

			if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
			{
				stringstream ss;
				ss << tileType;
				string num = ss.str();
				if (tileType >= 10)
				{
					tiles[i] = new Object(x, y, tile + num + png, Renderer, false);
					if (tileType != 12)
						collision.push_back(tiles[i]->getCollider());
				}
				else
					if (tileType != 0)
					{
						tiles[i] = new Object(x, y, tile + zero + num + png, Renderer, false);
						collision.push_back(tiles[i]->getCollider());
					}
					else
						tiles[i] = new Object(x, y, tile + zero + num + png, Renderer);
			}
			else
			{
				printf("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}

			x += TILE_WIDTH;

			if (x >= LEVEL_WIDTH)
			{
				x = 0;

				y += TILE_HEIGHT;
			}
		}
	}

	map.close();
}

vector<SDL_Rect>& Map::getCollision()
{
	return collision;
}

void Map::render(SDL_Renderer* Renderer, SDL_Rect& camera)
{
	for (int i = 0; i < TOTAL_TILES;i++)
	{
		if (checkCollision(camera,tiles[i]->getCollider()))
		{
			tiles[i]->render(Renderer, camera);
		}
	}
}
