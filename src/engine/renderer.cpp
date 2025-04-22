#include "renderer.h"

#include "dbg.h"

#include <cstdlib>

using namespace resimdbg;

Renderer::Renderer(SDL_Window *hdl)
{
    this->handle = SDL_CreateRenderer(hdl, -1, 0);
    if(pushErrorCheck(ERRTYPE_FAIL_CREATE_RND, handle == nullptr))
        std::exit(-2);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(handle);
}

void Renderer::texCopy(SDL_Texture *tex, SDL_Rect *srcrct, SDL_Rect *dstrct)
{
    SDL_RenderCopy(handle, tex, srcrct, dstrct);
}

void Renderer::clearScreen()
{
    SDL_RenderFillRect(handle, nullptr);
}

void Renderer::present()
{
    SDL_RenderPresent(handle);
}

SDL_Renderer *Renderer::getHandle()
{
    return handle;
}
