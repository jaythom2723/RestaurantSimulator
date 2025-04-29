#include "employee.h"

#include "common.h"
#include "dbg.h"
#include "aStar.h"
#include "engine.h"

Employee::Employee(Renderer& r, int empId, Vector2 pos, float speed)
    : Actor(r, "res/gfx/employee.bmp", pos, 32, 32, speed)
{
    this->empId = empId;

    allowedTasks = {
        TSKCLASS_BUSSING,
        TSKCLASS_CLEANING,
        TSKCLASS_COOKING,
        TSKCLASS_GUESTING,
        TSKCLASS_HAULING,
        TSKCLASS_HOSTING,
        TSKCLASS_MANAGING,
        TSKCLASS_SERVING
    };
}

Employee::~Employee()
{

}

void Employee::update(double deltaTime)
{
    getNextWaypoint();
    moveTowardsWaypoint(deltaTime);

    for (TaskClass cls : allowedTasks)
    {
        while (!EngineState::tasks[cls]->empty() && !task)
        {
            task = std::shared_ptr<Task>(EngineState::tasks[cls]->top());
            EngineState::tasks[cls]->pop();

            navPoint dest = Navmesh::Vector2ToMeshPoint(task.get()->getDest());
            choosePath(EngineState::mesh, dest);
        }
    }

    if (task && Vector2::GetDistance(calcOrigin(), task.get()->getDest()) <= 5)
    {
        task.get()->perform(deltaTime);

        if (task.get()->isComplete())
            task.reset();
    }
}

void Employee::draw(Renderer& r)
{
    SDL_Rect rect = {0};
    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = width;
    rect.h = height;

    r.texCopy(texture->getTexture(), nullptr, &rect);
}

int Employee::getEmpId()
{
    return empId;
}

const std::stack<navPoint>& Employee::getPath()
{
    return path;
}
