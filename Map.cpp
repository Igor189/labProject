#include"Map.h"
#include<fstream>
#include<sstream>
Map::Map(SDL_Renderer* Renderer)
{
	bool tilesLoaded = true;
	string tile = "Tiles/Tile_";
	string box = "box.png";
	string finish = "finish.png";
	string portIn = "Tiles/Portal_In.png";
	string portOut = "Tiles/Portal_Out.png";
	string enemy="Tiles/Spike_";
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
				if (tileType >= 10&&tileType<=60)
				{
					tiles[i] = new Object(x, y, tile + num + png, Renderer, false);
					if (tileType != 12&& tileType%10!=0)
						collision.push_back(tiles[i]->getCollider());
					if (tileType % 10 == 0)
						enemiesCollision.push_back(tiles[i]->getCollider());
				}
				else if (tileType < 10) 
				{
					if (tileType != 0)
					{
						tiles[i] = new Object(x, y, tile + zero + num + png, Renderer, false);
						collision.push_back(tiles[i]->getCollider());
					}
					else
						tiles[i] = new Object(x, y, tile + zero + num + png, Renderer);
				}
				else
					switch(tileType)
				{
					case 61:
						tiles[i]= new Object(x+8, y+16, enemy  + num + png, Renderer);
						enemiesCollision.push_back(tiles[i]->getCollider());
						break;
					case 62:
						tiles[i] = new Object(x, y + 8, enemy + num + png, Renderer);
						enemiesCollision.push_back(tiles[i]->getCollider());
						break;
					case 63:
						tiles[i] = new Object(x+8, y, enemy + num + png, Renderer);
						enemiesCollision.push_back(tiles[i]->getCollider());
						break;
					case 64:
						tiles[i] = new Object(x+16, y + 8, enemy + num + png, Renderer);
						enemiesCollision.push_back(tiles[i]->getCollider());
						break;
					case 65:
						tiles[i] = new Object(x + 8, y + 16, box, Renderer);
						collision.push_back(tiles[i]->getCollider());
						break;
					case 66:
						tiles[i] = new Object(x, y + 16, box, Renderer);
						collision.push_back(tiles[i]->getCollider());
						break;
					case 67:
						tiles[i] = new Object(x + 16, y + 16, box, Renderer);
						collision.push_back(tiles[i]->getCollider());
						break;
					case 68:
						tiles[i] = new Object(x, y, portIn, Renderer);
						teleport = tiles[i]->getCollider();
						break;
					case 69:
						tiles[i] = new Object(x, y, portOut, Renderer);
						break;
					case 70:
						tiles[i] = new Object(x, y, finish, Renderer);
						finishCollision = tiles[i]->getCollider();
						break;
					case 71:
						tiles[i] = new Object(x, y+24, enemy + num + png, Renderer);
						enemiesCollision.push_back(tiles[i]->getCollider());
						break;
					case 72:
						tiles[i] = new Object(x+24, y, enemy + num + png, Renderer);
						enemiesCollision.push_back(tiles[i]->getCollider());
						break;
				}

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

vector<SDL_Rect>& Map::getEnemiesCollision()
{
	return enemiesCollision;
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
	//if (checkCollision(camera, enemies[0]->getCollider()))
	//	enemies[0]->render(Renderer, camera);
}
SDL_Rect& Map::getTeleport()
{
	return teleport;
}
SDL_Rect& Map::getFinish()
{
	return finishCollision;
}
//void Map::addEnemies(SDL_Renderer* Renderer)
//{
//	enemies[0] = new Object(40, 208, "spike.png", Renderer);
//	enemies[0]->setCollider(13, 16);
//	enemiesCollision.push_back(enemies[0]->getCollider());
//}

