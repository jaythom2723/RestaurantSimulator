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

    Task task;

    virtual void onTaskComplete() {}
    virtual Vector2 getTaskDestination() {}

public:
    TaskEntity(Renderer &r, std::string path, Vector2 pos, int width, int height, float tbl);
    virtual ~TaskEntity() {}

    virtual void update(double deltaTime);
    virtual void draw(Renderer& r);

    float getInterval();
};

#endif // TASKENTITY_H_INCLUDED
