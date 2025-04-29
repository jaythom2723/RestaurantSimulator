#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

#include "common.h"

#include "taskentity.h"

class Table : public TaskEntity
{
protected:
    void onTaskComplete();
    Vector2 getTaskDestination();

public:
    Table(Renderer& r, navPoint pos);
    virtual ~Table() {}

    void update(double deltaTime);
    void draw(Renderer& r);
};

#endif // TABLE_H_INCLUDED
