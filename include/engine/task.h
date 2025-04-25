#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED

#include "common.h"
#include "actor.h"

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

    //Actor& performer;

    bool completed = false;
    bool infinite = false; // infinite task generation!!!
public:
    static const Task NULLTASK;
    static std::stack<std::pair<TaskClass, Task*>> openTasks;

    Task() {}
    Task(TaskType type, TaskClass cls, TaskDirection dir, bool infinite);
    ~Task();

    // broadcast the task to be located in the game world at (x,y)
    void broadcast(Vector2 dest);

    //void setPerformer(Actor& performer);

    TaskType getType();
    TaskClass getClass();
    TaskDirection getDir();

    Vector2 getDest();

    void complete();
    bool isComplete();
    bool isInfinite();

    //const Actor& getPerformer();
};

#endif // TASK_H_INCLUDED
