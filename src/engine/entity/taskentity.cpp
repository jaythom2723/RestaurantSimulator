#include "taskentity.h"

TaskEntity::TaskEntity(Renderer &r, std::string path, Vector2 pos, int width, int height, float tbl)
    : TexturedEntity(r, path, pos, width, height)
{
    taskBroadcastInterval = tbl;
    _tblResetValue = tbl;
}

void TaskEntity::update(double deltaTime)
{
    if (!intervalPaused)
        taskBroadcastInterval -= deltaTime;

    if (taskBroadcastInterval <= 0)
    {
        task.broadcast(getTaskDestination());
        taskBroadcastInterval = _tblResetValue;

        if (!task.isInfinite())
            intervalPaused = true;
    }

    if (task.isComplete())
        onTaskComplete();
}

void TaskEntity::draw(Renderer &r)
{
    SDL_Rect rect = { 0 };
    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = width;
    rect.h = height;

    r.texCopy(texture->getTexture(), nullptr, &rect);
}

float TaskEntity::getInterval()
{
    return taskBroadcastInterval;
}
