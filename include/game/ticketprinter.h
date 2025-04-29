#ifndef TICKETPRINTER_H_INCLUDED
#define TICKETPRINTER_H_INCLUDED

#include "common.h"

#include "taskentity.h"

class TicketPrinter : public TaskEntity
{
protected:
    void onTaskComplete();
    Vector2 getTaskDestination();

public:
    TicketPrinter(Renderer& r, navPoint pos);
    virtual ~TicketPrinter() {}

    void update(double deltaTime);
    void draw(Renderer& r);
};

#endif // TICKETPRINTER_H_INCLUDED
