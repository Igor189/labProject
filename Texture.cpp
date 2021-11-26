#include"Texture.h"
#include<iostream>
Texture::Texture()
{
	width = 0;
	height = 0;
	texture = NULL;
}
Texture::~Texture()
{
	free();
}
void Texture::free()
{
	SDL_DestroyTexture(texture);
	width = 0;
	height = 0;
	texture = NULL;
}
int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}

void Texture::render(int x, int y,SDL_Renderer* Renderer, SDL_Rect* rect)
{
	SDL_Rect renderQuad{ x,y,width,height };
	if (rect != NULL)
	{
		renderQuad.w = rect->w;
		renderQuad.h = rect->h;
	}
	SDL_RenderCopy(Renderer, texture, rect, &renderQuad);
}

bool Texture::loadFromFile(string fileName, SDL_Renderer* Renderer)
{
	SDL_Surface* loadedImg = IMG_Load(fileName.c_str());
	if (loadedImg == NULL)
	{
		cerr << "Unable to upload image: " << IMG_GetError() << "\n";
		return false;
	}
	SDL_SetColorKey(loadedImg, SDL_TRUE, SDL_MapRGB(loadedImg->format, 0, 255, 255));
	texture = SDL_CreateTextureFromSurface(Renderer, loadedImg);
	if (texture == NULL)
	{
		cerr << "it is not possible to create a texture from an image: " << SDL_GetError() << "\n";
		return false;
	}
	width = loadedImg->w;
	height = loadedImg->h;
	SDL_FreeSurface(loadedImg);
	return true;
}

