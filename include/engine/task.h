#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED

#include "common.h"
#include "actor.h"

#include <memory>
#include <cstdint>
#include <vector>

/*
    Broadcast masks determine what tasks can force entities to broadcast tasks
    (at their current stage)
*/
typedef enum {
    TSKMASK_NULL                        = 0x00, // 0b0000 0000
    TSKMASK_TICKET_PRINTER              = 0x01, // 0b0000 0001
    TSKMASK_TABLE                       = 0x02, // 0b0000 0010
    TSKMASK_STOOL                       = 0x04, // 0b0000 0100
    TSKMASK_OVEN                        = 0x08, // 0b0000 1000
    TSKMASK_SERVING_TABLE               = 0x10, // 0b0001 0000
} TaskBroadcastMask;

/*
    Task Type determines what action to perform
*/
typedef enum {
    TSKTYPE_PICK_UP,
    TSKTYPE_PUT_DOWN,
    TSKTYPE_SERVE_FOOD,
    TSKTYPE_SPEAK,
    TSKTYPE_CLEAN,
    TSKTYPE_COOK,
    TSKTYPE_GREET,
    TSKTYPE_SEAT_SYSTEM, // seat the guest into the system
    TSKTYPE_SEAT_TABLE   // seat the guest into their chosen table
} TaskType;

/*
    Task Class determines which actors can perform this task
*/
typedef enum {
    TSKCLASS_COOKING,
    TSKCLASS_CLEANING,
    TSKCLASS_HAULING,
    TSKCLASS_BUSSING,
    TSKCLASS_HOSTING,
    TSKCLASS_SERVING,
    TSKCLASS_MANAGING,
    TSKCLASS_GUESTING
} TaskClass;

/*
    Tasks may or may not have a direction tied to them as well
*/
typedef enum
{
    TSKDIR_NULL,
    TSKDIR_LOCATIVE, // task is located where the performer currently is
    TSKDIR_NORTH,
    TSKDIR_SOUTH,
    TSKDIR_EAST,
    TSKDIR_WEST,
    TSKDIR_NORTH_EAST,
    TSKDIR_NORTH_WEST,
    TSKDIR_SOUTH_EAST,
    TSKDIR_SOUTH_WEST
} TaskDirection;

class Task
{
private:
    TaskType type;
    TaskClass cls;
    TaskDirection dir;

    Vector2 destination;

    bool completed = false;
    bool infinite = false; // infinite task generation!!!

    double completionTimer;
    double _timerReset;

    TaskBroadcastMask taskBroadcastMask;
public:
    static const Task NULLTASK;

    // broadcast the task to be located in the game world at (x,y)
    static void Broadcast(std::shared_ptr<Task> task, Vector2 dest);

    Task() {}
    Task(TaskType type, TaskClass cls, TaskDirection dir, bool infinite, double completionTimer, TaskBroadcastMask mask);
    ~Task();

    void perform(double deltaTime); // used by the employee

    TaskType getType();
    TaskClass getClass();
    TaskDirection getDir();

    void setDest(Vector2 v);
    Vector2 getDest();

    const TaskBroadcastMask& getBroadcastMask();

    void setComplete(bool value);
    bool isComplete();
    bool isInfinite();
};

#endif // TASK_H_INCLUDED
