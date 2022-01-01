#include"Player.h"
#include<iostream>
#include"Timer.h"
#include<fstream>
#include"Map.h"
#include <SDL_mixer.h>
#include"Button.h"
using namespace std;

SDL_Renderer* Renderer;
SDL_Window* Window;
Mix_Music* mainMusic = NULL;
Mix_Music* diedMusic = NULL;
Mix_Music* endMusic = NULL;
Texture buttonTexture;

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO) < 0)
	{
		cerr << "cant init SDL: " << SDL_GetError();
		success = false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cerr<<"SDL_mixer could not initialize! SDL_mixer Error: %s\n"<< Mix_GetError();
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
	Mix_FreeMusic(mainMusic);
	Mix_FreeMusic(diedMusic);
	mainMusic = NULL;
	diedMusic = NULL;
	IMG_Quit();
	Mix_Quit();
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
		mainMusic = Mix_LoadMUS("FarBeyond Studio - Freebies Vol. 1 - 01 - Enchanted Woods (CC-BY 4.0).ogg");
		diedMusic = Mix_LoadMUS("you-died-sound.mp3");
		endMusic = Mix_LoadMUS("end_sound.mp3");
		Player play(0,204, "hero.png",Renderer);
		Texture bgTexture;
		Texture playButton;
		Texture musicButton;
		Texture exitButton;
		playButton.loadFromFile("buttons/play.png", Renderer);
		musicButton.loadFromFile("buttons/music.png", Renderer);
		exitButton.loadFromFile("buttons/exit.png", Renderer);
		buttonTexture.loadFromFile("button.png", Renderer);
		Button buttons[3];
		for (int i = 0; i < 3; i++)
		{
			buttons[i].setPosition(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2,100+i*100);
		}
		Texture deadTexture;
		Texture menuTexture;
		Texture endTexture;
		Map testMap(Renderer);
		bgTexture.loadFromFile("bg.jpg", Renderer);
		deadTexture.loadFromFile("deadImg.jpg", Renderer);
		menuTexture.loadFromFile("menu.jpg", Renderer);
		endTexture.loadFromFile("end.jpg", Renderer);
		int scrollingOffset = 0;
		bool gameLoop = false;
		bool exit = false;
		bool music = true;
		SDL_Event e;
		Timer stepTimer;
		SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		Mix_PlayMusic(mainMusic, -1);
		while (!exit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					exit = true;
				}
				if (buttons[0].handleEvent(&e))
				{
					gameLoop = true;
				}
				if (buttons[1].handleEvent(&e))
				{
					if (Mix_PlayingMusic() == 0)
					{
						Mix_PlayMusic(mainMusic, -1);
						music = true;
					}
					else
					{
						if (Mix_PausedMusic() == 1)
						{
							music = true;
							Mix_ResumeMusic();
						}
						else
						{
							music = false;
							Mix_PauseMusic();
						}
					}
				}
				if (buttons[2].handleEvent(&e))
				{
					exit = true;
				}
			}
			play.setPos(0, 204);
			SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(Renderer);
			menuTexture.render(0, 0, Renderer);
			for (int i = 0; i < TOTAL_BUTTONS; ++i)
			{
				buttons[i].render(Renderer,buttonTexture);
			}
			playButton.render(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 100,Renderer);
			musicButton.render(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 200, Renderer);
			exitButton.render(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 300, Renderer);
			SDL_RenderPresent(Renderer);
			while (gameLoop)
			{
				while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
					{
						gameLoop = false;
					}
					play.handleEvent(e, testMap.getCollision());
				}
				float timeStep = stepTimer.getTicks() / 1000.f;
				play.move(testMap.getCollision(), timeStep);
				play.teleport(testMap.getTeleport());
				stepTimer.start();
				if (checkCollision(testMap.getEnemiesCollision(), play.getCollider()))
				{
					deadTexture.render(0, 0, Renderer);
					SDL_RenderPresent(Renderer);
					if (music)
					{
						Mix_HaltMusic();
						Mix_PlayMusic(diedMusic, -1);
					}
					SDL_Delay(8000);
					gameLoop = false;
					if (music)
					{
						Mix_HaltMusic();
						Mix_PlayMusic(mainMusic, -1);
					}
				}
				if (checkCollision(testMap.getFinish(), play.getCollider()))
				{
					gameLoop = false;
					endTexture.render(0, 0, Renderer);
					SDL_RenderPresent(Renderer);
					if (music)
					{
						Mix_HaltMusic();
						Mix_PlayMusic(endMusic, -1);
					}
					SDL_Delay(5000);
					gameLoop = false;
					if (music)
					{
						Mix_HaltMusic();
						Mix_PlayMusic(mainMusic, -1);
					}
				}
				SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
				SDL_RenderClear(Renderer);
				bgTexture.render(0, 0, Renderer);
				testMap.render(Renderer, camera);
				play.render(Renderer, camera);
				play.setCamera(camera);
				SDL_RenderPresent(Renderer);
			}
		}
	}
	close();
	return 0;
}