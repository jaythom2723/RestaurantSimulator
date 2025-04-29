#include "common.h"

#include "dbg.h"
#include "display.h"
#include "renderer.h"
#include "texture.h"
#include "texturedentity.h"
#include "employee.h"
#include "taskentity.h"
#include "puddle.h"
#include "task.h"
#include "table.h"
#include "ticketprinter.h"

#include "engine.h"

bool init();
void close();
void update(double deltaTime);
void draw(Renderer& r);

int main(int argc, char *argv[])
{
    using namespace resimdbg;

    if(pushErrorCheck(ERRTYPE_FAIL_INIT_SDL, SDL_Init(SDL_INIT_VIDEO) < 0))
        return -2;

    Display d("Restaurant Simulator", 800, 600);
    Renderer r(d.getHandle());

    EngineState::mesh.blockCellAt(15, 10);
    EngineState::mesh.blockCellAt(10, 5);

    init();

    SDL_Event e;
    bool quit = false;

    float now = (float) SDL_GetPerformanceCounter();
    float last = 0.0f;
    double deltaTime = 0.0f;

    EngineState::SpawnEntity<Employee>(r, 0, (Vector2) Navmesh::MeshPointToWorldPoint({0, 0}), 125.0f);
    EngineState::SpawnEntity<Table>(r, (navPoint){1, 0});
    EngineState::SpawnEntity<TicketPrinter>(r, (navPoint){2, 0});

    while (!quit)
    {
        deltaTime = EngineState::GetDT(&now, &last);

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        update(deltaTime);
        draw(r);

        SDL_UpdateWindowSurface(d.getHandle());
    }

    close();

    return 0;
}

bool init()
{
    // TODO: Is there a way to make this programmatic and less ugly?
    EngineState::tasks[TSKCLASS_BUSSING] = new std::stack<std::shared_ptr<Task>>();
    EngineState::tasks[TSKCLASS_CLEANING] = new std::stack<std::shared_ptr<Task>>();
    EngineState::tasks[TSKCLASS_COOKING] = new std::stack<std::shared_ptr<Task>>();
    EngineState::tasks[TSKCLASS_GUESTING] = new std::stack<std::shared_ptr<Task>>();
    EngineState::tasks[TSKCLASS_HAULING] = new std::stack<std::shared_ptr<Task>>();
    EngineState::tasks[TSKCLASS_HOSTING] = new std::stack<std::shared_ptr<Task>>();
    EngineState::tasks[TSKCLASS_MANAGING] = new std::stack<std::shared_ptr<Task>>();
    EngineState::tasks[TSKCLASS_SERVING] = new std::stack<std::shared_ptr<Task>>();

    return true;
}

void close()
{
    delete EngineState::tasks[TSKCLASS_BUSSING];
    delete EngineState::tasks[TSKCLASS_CLEANING];
    delete EngineState::tasks[TSKCLASS_COOKING];
    delete EngineState::tasks[TSKCLASS_GUESTING];
    delete EngineState::tasks[TSKCLASS_HAULING];
    delete EngineState::tasks[TSKCLASS_HOSTING];
    delete EngineState::tasks[TSKCLASS_MANAGING];
    delete EngineState::tasks[TSKCLASS_SERVING];

    SDL_Quit();
}

void update(double deltaTime)
{
    for (int i = 0; i < EngineState::entities.size(); i++)
    {
        EngineState::entities[i]->update(deltaTime);
    }
}

void draw(Renderer& r)
{
    r.clearScreen();

    for (int i = 0; i < EngineState::entities.size(); i++)
    {
        EngineState::entities[i]->draw(r);
    }

    r.present();
}
