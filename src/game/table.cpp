#include "table.h"

#include "task.h"
#include "engine.h"
#include <memory>

Table::Table(Renderer& r, navPoint pos)
    : TaskEntity(r, "res/gfx/table.bmp", pos, 32, 32, 2, TSKMASK_TABLE)
{
    taskStages.push_back(std::make_shared<Task>(TSKTYPE_GREET, TSKCLASS_SERVING, TSKDIR_SOUTH, false, 2, TSKMASK_TICKET_PRINTER));
    taskStages.push_back(std::make_shared<Task>(TSKTYPE_SERVE_FOOD, TSKCLASS_SERVING, TSKDIR_SOUTH, false, 2, TSKMASK_TABLE));
    taskStages.push_back(std::make_shared<Task>(TSKTYPE_CLEAN, TSKCLASS_BUSSING, TSKDIR_SOUTH, false, 2, TSKMASK_NULL));

    this->pos = calcOrigin();
}

void Table::onTaskComplete()
{
    TaskEntity::onTaskComplete();
}

Vector2 Table::getTaskDestination()
{
    Vector2 destPos = (Vector2) Navmesh::MeshPointToWorldPoint(meshPos);
    destPos.y += 64;
    destPos.x += width / 2;
    return destPos;
}

void Table::update(double deltaTime)
{
    TaskEntity::update(deltaTime);
}

void Table::draw(Renderer& r)
{
    TaskEntity::draw(r);
}
