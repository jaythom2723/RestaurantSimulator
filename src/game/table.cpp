#include "table.h"

#include "task.h"
#include "engine.h"
#include <memory>

void Table::onTaskComplete()
{
    TaskEntity::onTaskComplete();
}

Vector2 Table::getTaskDestination()
{
    navPoint tmp = Navmesh::MeshPointToWorldPoint((navPoint) {4, 2});
    return Vector2(tmp.x, tmp.y);
}

Table::Table(Renderer& r, Vector2 pos)
    : TaskEntity(r, "res/gfx/table.bmp", pos, 32, 32, 2)
{
    taskStages.push_back(std::make_shared<Task>(TSKTYPE_GREET, TSKCLASS_SERVING, TSKDIR_SOUTH, false, 2));
    taskStages.push_back(std::make_shared<Task>(TSKTYPE_SERVE_FOOD, TSKCLASS_SERVING, TSKDIR_SOUTH, false, 2));
    taskStages.push_back(std::make_shared<Task>(TSKTYPE_CLEAN, TSKCLASS_BUSSING, TSKDIR_SOUTH, false, 2));

    this->pos = calcOrigin();
}

void Table::update(double deltaTime)
{
    TaskEntity::update(deltaTime);
}

void Table::draw(Renderer& r)
{
    TaskEntity::draw(r);
}
