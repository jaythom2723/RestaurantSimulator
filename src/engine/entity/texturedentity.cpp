#include "texturedentity.h"

TexturedEntity::TexturedEntity(Renderer& r, std::string path, Vector2 pos, int width, int height)
    : Entity(pos, width, height)
{
    texture = new Texture(r, path);
}

TexturedEntity::~TexturedEntity()
{
    delete texture;
}


void TexturedEntity::draw(Renderer& r)
{
    SDL_Rect rect = { 0 };
    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = width;
    rect.h = height;

    r.texCopy(texture->getTexture(), nullptr, &rect);
}
