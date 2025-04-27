#include "puddle.h"

#include "engine.h"

Puddle::Puddle(Renderer& r, Vector2 pos)
    : TaskEntity(r, "res/gfx/puddle.bmp", pos, 32, 32, 2)
{
    this->pos = calcOrigin();

    taskStages.push_back(std::make_shared<Task>(TSKTYPE_CLEAN, TSKCLASS_CLEANING, TSKDIR_LOCATIVE, false, 2));
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
    TaskEntity::onTaskComplete();

    EngineState::DestroyEntity(this);
}

Vector2 Puddle::getTaskDestination()
{
    return calcOrigin(); // literally just our position
}
