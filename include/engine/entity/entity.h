#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "common.h"

#include "display.h"
#include "renderer.h"

class Entity
{
protected:
    Vector2 pos;

    int id;
    int width, height;

    Vector2 calcOrigin();

public:
    Entity(Vector2 pos, int width, int height);
    Entity(int x, int y, int w, int h);
    virtual ~Entity() {}

    virtual void update(double deltaTime) {}
    virtual void draw(Renderer& r) {}

    void setPos(Vector2 pos);
    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);

    Vector2 getPos();
    int getX();
    int getY();
    int getWidth();
    int getHeight();

    const int getId();
};

#endif // ENTITY_H_INCLUDED
