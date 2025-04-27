#include "taskentity.h"

#include "engine.h"

void TaskEntity::onTaskComplete()
{
    curStage++;

    if (curStage > taskStages.size())
        intervalPaused = true;
}

TaskEntity::TaskEntity(Renderer &r, std::string path, Vector2 pos, int width, int height, float tbl)
    : TexturedEntity(r, path, pos, width, height)
{
    taskBroadcastInterval = tbl;
    _tblResetValue = tbl;
}

void TaskEntity::update(double deltaTime)
{
    if (!taskStages[curStage])
        return;

    if (!intervalPaused)
        taskBroadcastInterval -= deltaTime;

    if (curStage < taskStages.size() && (intervalPaused && taskStages[curStage].get()->isComplete()))
        intervalPaused = false;

    if (taskBroadcastInterval <= 0)
    {
        Task::Broadcast(taskStages[curStage], getTaskDestination());
        taskBroadcastInterval = _tblResetValue;

        if (!taskStages[curStage].get()->isComplete())
            intervalPaused = true;
    }

    if (taskStages[curStage].get()->isComplete())
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
