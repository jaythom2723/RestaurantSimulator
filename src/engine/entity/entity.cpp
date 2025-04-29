#include "entity.h"

#include "engine.h"

Vector2 Entity::calcOrigin()
{
    return Vector2(pos.x + (width / 2), pos.y + (height / 2));
}

Entity::Entity(Vector2 pos, int width, int height)
{
    id = EngineState::entities.size();

    this->pos = pos;
    this->width = width;
    this->height = height;
}

Entity::Entity(int x, int y, int w, int h)
{
    this->pos = Vector2(x, y);
    this->width = w;
    this->height = h;
}

void Entity::setPos(Vector2 pos)
{
    this->pos = pos;
}

void Entity::setX(int x)
{
    this->pos.x = x;
}

void Entity::setY(int y)
{
    this->pos.y = y;
}

void Entity::setWidth(int width)
{
    this->width = width;
}

void Entity::setHeight(int height)
{
    this->height = height;
}

Vector2 Entity::getPos()
{
    return pos;
}

int Entity::getX()
{
    return pos.x;
}

int Entity::getY()
{
    return pos.y;
}

int Entity::getWidth()
{
    return width;
}

int Entity::getHeight()
{
    return height;
}

const int Entity::getId()
{
    return id;
}
