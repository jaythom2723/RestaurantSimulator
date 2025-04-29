#ifndef PUDDLE_H_INCLUDED
#define PUDDLE_H_INCLUDED

#include "common.h"

#include "taskentity.h"

class Puddle : public TaskEntity
{
protected:
    void onTaskComplete();
    Vector2 getTaskDestination();

public:
    Puddle(Renderer &r, navPoint pos);
    virtual ~Puddle() {}

    void update(double deltaTime);
    void draw(Renderer& r);
};

#endif // PUDDLE_H_INCLUDED
