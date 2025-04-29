#include "task.h"

#include "engine.h"

void Task::Broadcast(std::shared_ptr<Task> task, Vector2 dest)
{
    task.get()->setDest(dest);
    EngineState::tasks[task.get()->getClass()]->push(std::shared_ptr<Task>(task));
}

Task::Task(TaskType type, TaskClass cls, TaskDirection dir, bool infinite, double completionTimer, TaskBroadcastMask bMask)
{
    this->type = type;
    this->cls = cls;
    this->dir = dir;
    this->infinite = infinite;
    this->completionTimer = completionTimer;
    this->_timerReset = completionTimer;
    this->taskBroadcastMask = bMask;
}

Task::~Task()
{

}

void Task::perform(double deltaTime)
{
    if (!completed)
        completionTimer -= deltaTime;

    if (completionTimer <= 0)
    {
        completionTimer = _timerReset;
        completed = true;
    }
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

const TaskBroadcastMask& Task::getBroadcastMask()
{
    return taskBroadcastMask;
}

void Task::setComplete(bool value)
{
    completed = value;
}

bool Task::isComplete()
{
    return completed;
}

bool Task::isInfinite()
{
    return infinite;
}
