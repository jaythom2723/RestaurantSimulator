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
