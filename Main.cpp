#include"Player.h"
#include<iostream>
#include"Timer.h"
#include<fstream>
using namespace std;




SDL_Renderer* Renderer;
SDL_Window* Window;
//Texture tileTexture;

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0)
	{
		cerr << "cant init SDL: " << SDL_GetError();
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cerr << "Warning: Linear texture filtering not enabled!";
		}
		Window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (Window == NULL)
		{
			cerr << "Window could not be crated: " << SDL_GetError();
			success = false;
		}
		else
		{
			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_PRESENTVSYNC);
			if (Renderer == NULL)
			{
				cerr << "Renderer could not be created: " << SDL_GetError();
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}
void close()
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	Window = NULL;
	Renderer = NULL;
	IMG_Quit();
	SDL_Quit();
}





int main(int argc, char* args[])
{
	if (!init())
	{
		cerr << "Cannot init libraries";
	}
	else
	{
		Player play(0,220, "hero.png",Renderer);
		Texture bgTexture;
		bgTexture.loadFromFile("nebo.png", Renderer);
		Object wall(220, 220, "Bricks.png", Renderer);
		Object ground(0, 240, "2dplatform.png", Renderer);
		Object enemy(400, 230, "enemy.png", Renderer);
		SDL_Rect groundRect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT / 2 };
		SDL_Rect wallRect{ 0,0,20,20 };
		vector <SDL_Rect> enemies;
		enemies.push_back(enemy.getCollider());
		vector<SDL_Rect> collision;
		collision.push_back(wall.getCollider());
		collision.push_back(ground.getCollider());
		int scrollingOffset = 0;
		bool quit = false;
		SDL_Event e;
		Timer stepTimer;
		//SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		while (!quit)
		{		
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = true;
				}
				play.handleEvent(e, collision);
			}
			float timeStep = stepTimer.getTicks() / 1000.f;
			play.move(collision,timeStep);
			//play.setCamera(camera);
			if (checkCollision(enemies, play.getCollider()))
			{
				quit = true;
			}
			stepTimer.start();
			scrollingOffset -= play.getVelX()*timeStep;
			if (scrollingOffset < -bgTexture.getWidth()||scrollingOffset>bgTexture.getWidth())
			{
				scrollingOffset = 0;
			}
			SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
			SDL_RenderClear(Renderer);
			bgTexture.render(scrollingOffset, 0,Renderer);
			bgTexture.render(scrollingOffset + bgTexture.getWidth(), 0,Renderer);
			bgTexture.render(scrollingOffset - bgTexture.getWidth(), 0, Renderer);
			enemy.render(Renderer);
			ground.render(Renderer, &groundRect);
			wall.render(Renderer);
			play.render(Renderer);
			SDL_RenderPresent(Renderer);
		}
	}
	close();
	return 0;
}