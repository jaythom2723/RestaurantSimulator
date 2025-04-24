#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include "renderer.h"

#include "common.h"

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
