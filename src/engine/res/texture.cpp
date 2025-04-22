#include "texture.h"

#include "dbg.h"

Texture::Texture(Renderer &r, std::string path)
{
    using namespace resimdbg;

    SDL_Surface *tmp = SDL_LoadBMP(path.c_str());
    if (pushErrorCheck(ERRTYPE_FAIL_LOAD_IMAGE, tmp == nullptr))
        std::printf("Could not find texture, '%s'\n", path.c_str());
    else
        std::printf("Found texture, '%s'\n", path.c_str());

    tex = SDL_CreateTextureFromSurface(r.getHandle(), tmp);

    SDL_FreeSurface(tmp);
}

Texture::~Texture()
{
    SDL_DestroyTexture(tex);
}

SDL_Texture *Texture::getTexture()
{
    return tex;
}
