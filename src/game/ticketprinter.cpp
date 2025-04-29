#include "ticketprinter.h"

#include "task.h"

TicketPrinter::TicketPrinter(Renderer& r, navPoint pos)
    : TaskEntity(r, "res/gfx/ticket_printer.bmp", pos, 32, 32, TSKMASK_TICKET_PRINTER)
{
    taskStages.push_back(std::make_shared<Task>(TSKTYPE_PICK_UP, TSKCLASS_COOKING, TSKDIR_SOUTH, false, 0.25, TSKMASK_OVEN));

    this->pos = calcOrigin();
}

void TicketPrinter::onTaskComplete()
{
    TaskEntity::onTaskComplete();

    std::printf("Ticket Printer Task Completed!\n");
}

Vector2 TicketPrinter::getTaskDestination()
{
    navPoint tmp = Navmesh::MeshPointToWorldPoint((navPoint) {7,4});
    return Vector2(tmp.x, tmp.y);
}

void TicketPrinter::update(double deltaTime)
{
    TaskEntity::update(deltaTime);
}

void TicketPrinter::draw(Renderer& r)
{
    TaskEntity::draw(r);
}
