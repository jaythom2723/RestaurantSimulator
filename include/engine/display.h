#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include "common.h"

class Display
{
private:
    std::string title;
    int width, height;
    SDL_Window *handle;
    SDL_Surface *surface;

public:
    Display(std::string title, int width, int height);
    ~Display();

    std::string getTitle();
    int getWidth();
    int getHeight();
    SDL_Window *getHandle();
    SDL_Surface *getSurface();
    SDL_PixelFormat *getFormat();
};

#endif // DISPLAY_H_INCLUDED
