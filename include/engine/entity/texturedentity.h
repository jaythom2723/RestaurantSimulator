#ifndef TEXTUREDENTITY_H_INCLUDED
#define TEXTUREDENTITY_H_INCLUDED

#include "common.h"
#include "vector.h"

#include "entity.h"
#include "texture.h"

class TexturedEntity : public Entity
{
protected:
    Texture *texture;

public:
    TexturedEntity(Renderer& r, std::string path, Vector2 pos, int width, int height);
    virtual ~TexturedEntity();
};

#endif // TEXTUREDENTITY_H_INCLUDED
