#include "puddle.h"

Puddle::Puddle(Renderer& r, Vector2 pos)
    : TaskEntity(r, "res/gfx/puddle.bmp", pos, 32, 32, 2)
{
    this->pos = calcOrigin();

    task = std::make_shared<Task>(TSKTYPE_CLEAN, TSKCLASS_CLEANING, TSKDIR_LOCATIVE, false, 2);
}

void Puddle::update(double deltaTime)
{
    TaskEntity::update(deltaTime);
}

void Puddle::draw(Renderer& r)
{
    TaskEntity::draw(r);
}

void Puddle::onTaskComplete()
{
    // TODO: kill self

    std::printf("Puddle task is complete!!!!!\n");
}

Vector2 Puddle::getTaskDestination()
{
    return pos; // literally just our position
}
