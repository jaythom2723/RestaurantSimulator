#include "entity.h"

Entity::Entity(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
}

void Entity::setX(int x)
{
    this->x = x;
}

void Entity::setY(int y)
{
    this->y = y;
}

void Entity::setWidth(int width)
{
    this->width = width;
}

void Entity::setHeight(int height)
{
    this->height = height;
}

int Entity::getX()
{
    return x;
}

int Entity::getY()
{
    return y;
}

int Entity::getWidth()
{
    return width;
}

int Entity::getHeight()
{
    return height;
}
