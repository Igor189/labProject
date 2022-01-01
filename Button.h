#pragma once
#include"Texture.h"
const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 60;
const int TOTAL_BUTTONS = 3;

enum ButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};
class Button
{
public:
    Button();

    void loadFromFile(SDL_Renderer* Renderer);

    void setPosition(int x, int y);

    bool handleEvent(SDL_Event* e);

    void render(SDL_Renderer* Renderer,Texture& buttonTexture);

private:
    SDL_Point pos;
    SDL_Rect spriteClips[BUTTON_SPRITE_TOTAL];
    ButtonSprite currentSprite;
};