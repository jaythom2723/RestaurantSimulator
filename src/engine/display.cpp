#include "display.h"

#include "dbg.h"

#include <cstdlib>

Display::Display(std::string title, int width, int height)
{
    using namespace resimdbg;

    this->title = title;
    this->width = width;
    this->height = height;

    handle = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (pushErrorCheck(ERRTYPE_FAIL_CREATE_WND, handle == nullptr))
        std::exit(-2);

    // surface = SDL_GetWindowSurface(handle);
}

Display::~Display()
{
    SDL_DestroyWindow(handle);
    handle = nullptr;
}

std::string Display::getTitle()
{
    return title;
}

int Display::getWidth()
{
    return width;
}

int Display::getHeight()
{
    return height;
}

SDL_Window *Display::getHandle()
{
    return handle;
}

SDL_Surface *Display::getSurface()
{
    return surface;
}

SDL_PixelFormat *Display::getFormat()
{
    return surface->format;
}
