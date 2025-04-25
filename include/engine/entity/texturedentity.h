#ifndef TEXTUREDENTITY_H_INCLUDED
#define TEXTUREDENTITY_H_INCLUDED

#include "common.h"

#include "entity.h"
#include "texture.h"

class TexturedEntity : public Entity
{
protected:
    Texture *texture;

public:
    TexturedEntity(Renderer& r, std::string path, Vector2 pos, int width, int height);
    virtual ~TexturedEntity();

    void draw(Renderer& r);
};

#endif // TEXTUREDENTITY_H_INCLUDED
