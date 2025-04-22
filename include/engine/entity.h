#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "transform.h"

#include "display.h"
#include "renderer.h"

class Entity
{
protected:
    TransformComponent tform;

public:
    Entity(int x, int y, int w, int h);
    virtual ~Entity() {}

    virtual void update(float deltaTime) {}
    virtual void draw(Renderer& r) {}

    TransformComponent &getTransform();
};

#endif // ENTITY_H_INCLUDED
