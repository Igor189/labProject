#include "Button.h"
#include<SDL_mixer.h>
Button::Button()
{
    for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i)
    {
        spriteClips[i].x = 0;
        spriteClips[i].y = i * 200;
        spriteClips[i].w = BUTTON_WIDTH;
        spriteClips[i].h = BUTTON_HEIGHT;
    }
    pos.x = 0;
    pos.y = 0;

    currentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

//void Button::loadFromFile(SDL_Renderer* Renderer)
//{
//    buttonTexture.loadFromFile("17_mouse_events/button.png", Renderer);
//}

void Button::setPosition(int x, int y)
{
    pos.x = x;
    pos.y = y;
}
bool Button::handleEvent(SDL_Event* e)
{
    bool ret = false;
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;

        if (x < pos.x)
        {
            inside = false;
        }
        else if (x > pos.x + BUTTON_WIDTH)
        {
            inside = false;
        }
        else if (y < pos.y)
        {
            inside = false;
        }
        else if (y > pos.y + BUTTON_HEIGHT)
        {
            inside = false;
        }
        if (!inside)
        {
            currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        else
        {
            switch (e->type)
            {
            case SDL_MOUSEMOTION:
                currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;

            case SDL_MOUSEBUTTONDOWN:
                currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;

            case SDL_MOUSEBUTTONUP:
                currentSprite = BUTTON_SPRITE_MOUSE_UP;
                ret = true;
                break;
            }
        }
    }
    return ret;
}
void Button::render(SDL_Renderer* Renderer,Texture& buttonTexture)
{
    buttonTexture.render(pos.x, pos.y,Renderer, &spriteClips[currentSprite]);
}