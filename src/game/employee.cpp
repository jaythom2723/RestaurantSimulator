#include "employee.h"

#include "common.h"
#include "dbg.h"
#include "aStar.h"

Employee::Employee(Renderer& r, int id, Vector2 pos, float speed)
    : Actor(r, "res/gfx/employee.bmp", pos, 32, 32, speed)
{
    this->id = id;
}

Employee::~Employee()
{

}

void Employee::update(double deltaTime, Navmesh& mesh)
{
    getNextWaypoint();
    moveTowardsWaypoint(deltaTime);

    while (Task::openTasks.size() > 0 && !task)
    {
        std::pair<TaskClass,Task*> top = Task::openTasks.top();
        Task::openTasks.pop();

        // TODO: Check employee and task class against each other

        // for now, just do any task that appears
        task = top.second;
        choosePath(mesh, Navmesh::Vector2ToMeshPoint(task->getDest()));
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
