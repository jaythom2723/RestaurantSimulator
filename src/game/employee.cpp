#include "employee.h"

#include "common.h"
#include "dbg.h"
#include "aStar.h"
#include "engine.h"

Employee::Employee(Renderer& r, int id, Vector2 pos, float speed)
    : Actor(r, "res/gfx/employee.bmp", pos, 32, 32, speed)
{
    this->id = id;
}

Employee::~Employee()
{

}

void Employee::update(double deltaTime)
{
    getNextWaypoint();
    moveTowardsWaypoint(deltaTime);

    // TODO: check against a list of allowed job types
    // TODO: check against the type of actor AKA "check the task class"
    while (!EngineState::tasks[TSKCLASS_CLEANING]->empty() && !task)
    {
        task = std::shared_ptr<Task>(EngineState::tasks[TSKCLASS_CLEANING]->top());
        EngineState::tasks[TSKCLASS_CLEANING]->pop();

        navPoint dest = Navmesh::Vector2ToMeshPoint(task.get()->getDest());
        choosePath(EngineState::mesh, dest);
    }

    if (task && Vector2::GetDistance(pos, task.get()->getDest()) <= 5)
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

    if (curWaypoint.x != -1 && curWaypoint.y != -1)
    {
        SDL_SetRenderDrawColor(r.getHandle(), 0xff, 0x00, 0x00, 0xff);
        SDL_RenderDrawPoint(r.getHandle(), curWaypoint.x, curWaypoint.y);
    }
}

int Employee::getId()
{
    return id;
}

const std::stack<navPoint>& Employee::getPath()
{
    return path;
}
