#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include "common.h"

class Renderer
{
private:
    SDL_Renderer *handle;

public:
    Renderer(SDL_Window *hdl);
    ~Renderer();

    void texCopy(SDL_Texture *tex, SDL_Rect *srcrct, SDL_Rect *dstrct);

    void clearScreen();
    void present();

    SDL_Renderer *getHandle();
};

#endif // RENDERER_H_INCLUDED
