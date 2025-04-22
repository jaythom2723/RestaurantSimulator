#include "entity.h"

Entity::Entity(int x, int y, int w, int h)
{
    tform.x = x;
    tform.y = y;
    tform.w = w;
    tform.h = h;
}

TransformComponent& Entity::getTransform()
{
    return tform;
}
