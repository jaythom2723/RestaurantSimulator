#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "display.h"
#include "renderer.h"

class Entity
{
protected:
    int x, y, width, height;

public:
    Entity(int x, int y, int w, int h);
    virtual ~Entity() {}

    virtual void update(float deltaTime) {}
    virtual void draw(Renderer& r) {}

    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);

    int getX();
    int getY();
    int getWidth();
    int getHeight();
};

#endif // ENTITY_H_INCLUDED
