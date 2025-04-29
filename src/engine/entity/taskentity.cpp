#include "taskentity.h"

#include "engine.h"
#include "utility.h"

TaskEntity::TaskEntity(Renderer &r, std::string path, navPoint pos, int width, int height, float tbl, TaskBroadcastMask bMask)
    : TexturedEntity(r, path, (Vector2) Navmesh::MeshPointToWorldPoint(pos), width, height)
{
    taskBroadcastInterval = tbl;
    _tblResetValue = tbl;
    broadcastMask = bMask;
    this->meshPos = pos;
}

TaskEntity::TaskEntity(Renderer &r, std::string path, navPoint pos, int width, int height, TaskBroadcastMask bMask)
    : TexturedEntity(r, path, (Vector2) Navmesh::MeshPointToWorldPoint(pos), width, height)
{
    broadcastMask = bMask;
    useInterval = false;
}

static const std::vector<std::string> validClassNames = {
    "Table", "TicketPrinter", "Oven"
};

void TaskEntity::checkBroadcastMask()
{
    Task *curTask = taskStages[curStage].get();
    const TaskBroadcastMask& mask = curTask->getBroadcastMask();

    if (mask == TSKMASK_NULL)
        return;

    int j = 0;
    int i, bit;

    // decode broadcast mask bitmask
    for (i = 1; i < TSKMASK_SERVING_TABLE + 1; i++)
    {
        bit = (mask & i) >> j;
        j++;

        if (bit == 0)
            continue;

        // search through all entities
        for (int w = 0; w < EngineState::entities.size(); w++)
        {
            std::string typeName = typeid(*(EngineState::entities[w].get())).name();

            // filter for task entities
            for (std::string n : validClassNames)
            {
                if (typeName.find(n) == std::string::npos)
                    continue;

                TaskEntity *tmp = dynamic_cast<TaskEntity*>(EngineState::entities[w].get());
                if (tmp->getBroadcastMask() == i)
                    tmp->broadcastInterrupt();
                tmp = nullptr;
            }
        }
    }

    curTask = nullptr;
}

void TaskEntity::onTaskComplete()
{
    checkBroadcastMask();
    curStage++;
}

void TaskEntity::update(double deltaTime)
{
    if (curStage > taskStages.size())
        curStage = 0;

    // probably redundant code
    if (taskStages[curStage].get() == nullptr || taskStages[curStage] == nullptr)
        return;

    if (useInterval)
    {
        if (curStage < taskStages.size() && (intervalPaused && taskStages[curStage]->isComplete()))
            intervalPaused = false;

        if (!intervalPaused)
            taskBroadcastInterval -= deltaTime;

        if (taskBroadcastInterval <= 0)
        {
            taskStages[curStage]->setComplete(false);
            Task::Broadcast(taskStages[curStage], getTaskDestination());
            taskBroadcastInterval = _tblResetValue;
            intervalPaused = true;
        }
    }

    if (taskStages[curStage]->isComplete())
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

TaskBroadcastMask TaskEntity::getBroadcastMask()
{
    return broadcastMask;
}

void TaskEntity::broadcastInterrupt()
{
    Task::Broadcast(taskStages[curStage], getTaskDestination());
    taskBroadcastInterval = _tblResetValue;

    if (!taskStages[curStage].get()->isComplete())
        intervalPaused = true;
}
