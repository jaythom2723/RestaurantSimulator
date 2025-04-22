#include "dbg.h"

#include <SDL2/SDL.h>

#include <string>

std::string getMessage(resimdbg::ErrorType t, bool *sdlRelated);

bool resimdbg::pushErrorCheck(resimdbg::ErrorType t, bool cond)
{
    if (cond)
    {
        bool sdlRelated = false;
        std::string msg = getMessage(t, &sdlRelated);

        if (sdlRelated)
        {
            std::printf("%s %s\n", msg.c_str(), SDL_GetError());
        } else
        {
            std::printf("%s\n", msg.c_str());
        }

        return true;
    }

    return false;
}

std::string getMessage(resimdbg::ErrorType t, bool *sdlRelated)
{
    switch(t)
    {
    case resimdbg::ERRTYPE_FAIL_INIT_SDL:
        (*sdlRelated) = true;
        return "Failed to initialize SDL2.\n\tSDL Error: ";
        break;
    case resimdbg::ERRTYPE_FAIL_CREATE_WND:
        (*sdlRelated) = true;
        return "Failed to create an SDL2 window.\n\tSDL Error: ";
        break;
    case resimdbg::ERRTYPE_FAIL_LOAD_IMAGE:
        (*sdlRelated) = true;
        return "Failed to load an image with SDL2.\n\tSDL Error: ";
        break;
    case resimdbg::ERRTYPE_FAIL_CREATE_RND:
        (*sdlRelated) = true;
        return "Failed to create an SDL2 renderer.\n\tSDL Error: ";
        break;
    default:
        return "";
        break;
    }
}
