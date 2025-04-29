#ifndef TASKENTITY_H_INCLUDED
#define TASKENTITY_H_INCLUDED

#include "common.h"

#include "task.h"
#include "texturedentity.h"

class TaskEntity : public TexturedEntity
{
protected:
    float taskBroadcastInterval;
    float _tblResetValue;

    bool intervalPaused = false;
    bool useInterval = true; // true by default

    int curStage = 0;

    TaskBroadcastMask broadcastMask;

    std::vector<std::shared_ptr<Task>> taskStages;

    navPoint meshPos; // the original mesh position that the entity is spawned at

    virtual void onTaskComplete();
    virtual Vector2 getTaskDestination() {}
    void checkBroadcastMask();

public:
    TaskEntity(Renderer &r, std::string path, navPoint pos, int width, int height, float tbl, TaskBroadcastMask bMask);
    TaskEntity(Renderer &r, std::string path, navPoint pos, int width, int height, TaskBroadcastMask bMask);
    virtual ~TaskEntity() {}

    virtual void update(double deltaTime);
    virtual void draw(Renderer& r);

    float getInterval();
    TaskBroadcastMask getBroadcastMask();
    void broadcastInterrupt();
};

#endif // TASKENTITY_H_INCLUDED
