#pragma once

#include <SDL.h>

class Entity {  

protected:
    SDL_Texture* texture;
    SDL_Rect rect;

    Entity(SDL_Texture* _texture);
    ~Entity();
};