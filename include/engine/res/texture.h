#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include "renderer.h"

#include <SDL2/SDL.h>

#include <string>

class Texture
{
private:
    SDL_Texture *tex;

public:
    Texture(Renderer &r, std::string path);
    ~Texture();

    SDL_Texture *getTexture();
};

#endif // TEXTURE_H_INCLUDED
