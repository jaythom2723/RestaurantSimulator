#include "task.h"

std::stack<std::pair<TaskClass, Task*>> Task::openTasks;

Task::Task(TaskType type, TaskClass cls, TaskDirection dir, bool infinite)
{
    this->type = type;
    this->cls = cls;
    this->dir = dir;
    this->infinite = infinite;
}

Task::~Task()
{

}

void Task::broadcast(Vector2 dest)
{
    this->destination = dest;

    openTasks.push(std::make_pair(cls, this));

    std::printf("My name is task and I've been broadcasted!!!!\n");
}

/*
void Task::setPerformer(Actor& performer)
{
    this->performer = performer;
}
*/

TaskType Task::getType()
{
    return type;
}

TaskClass Task::getClass()
{
    return cls;
}

TaskDirection Task::getDir()
{
    return dir;
}

Vector2 Task::getDest()
{
    return destination;
}

void Task::complete()
{
    completed = true;
}

bool Task::isComplete()
{
    return completed;
}

bool Task::isInfinite()
{
    return infinite;
}

/*
const Actor& Task::getPerformer()
{
    return performer;
}
*/
