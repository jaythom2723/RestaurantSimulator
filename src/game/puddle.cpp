#include "puddle.h"

Puddle::Puddle(Renderer& r, Vector2 pos)
    : TaskEntity(r, "res/gfx/puddle.bmp", pos, 32, 32, 2)
{
    task = Task(TSKTYPE_CLEAN, TSKCLASS_CLEANING, TSKDIR_LOCATIVE, false);
}

void Puddle::update(double deltaTime)
{
    TaskEntity::update(deltaTime);
}

void Puddle::draw(Renderer& r)
{
    TaskEntity::draw(r);

    /*
        SDL_Rect rect = {0};
        rect.x = pos.x;
        rect.y = pos.y;
        rect.w = width;
        rect.h = height;

        r.texCopy(texture->getTexture(), nullptr, &rect);

    */
}

void Puddle::onTaskComplete()
{
    // TODO: kill self
}

Vector2 Puddle::getTaskDestination()
{
    return pos; // literally just our position
}
