#include "task.h"

#include "engine.h"

void Task::Broadcast(std::shared_ptr<Task> task, Vector2 dest)
{
    task.get()->setDest(dest);
    EngineState::tasks[task.get()->getClass()]->push(std::shared_ptr<Task>(task));
}

Task::Task(TaskType type, TaskClass cls, TaskDirection dir, bool infinite, double completionTimer)
{
    this->type = type;
    this->cls = cls;
    this->dir = dir;
    this->infinite = infinite;
    this->completionTimer = completionTimer;
}

Task::~Task()
{

}

void Task::perform(double deltaTime)
{
    if (!completed)
        completionTimer -= deltaTime;

    if (completionTimer <= 0)
        completed = true;
}

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

void Task::setDest(Vector2 v)
{
    destination = v;
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
