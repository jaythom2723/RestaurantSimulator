#include "common.h"

#include "dbg.h"
#include "display.h"
#include "renderer.h"
#include "texture.h"
#include "texturedentity.h"
#include "employee.h"
#include "taskentity.h"
#include "puddle.h"

int main(int argc, char *argv[])
{
    using namespace resimdbg;

    if(pushErrorCheck(ERRTYPE_FAIL_INIT_SDL, SDL_Init(SDL_INIT_VIDEO) < 0))
        return -2;

    Display d("Test Window", 800, 600);
    Renderer r(d.getHandle());

    Employee emp(r, 0, (Vector2) Navmesh::MeshPointToWorldPoint((navPoint){ 0, 0 }), 125.0f);
    TexturedEntity wall(r, "res/gfx/wall1.bmp", (Vector2) Navmesh::MeshPointToWorldPoint((navPoint){10, 15}), 32, 32);
    TaskEntity t(r, "res/gfx/ticket_printer.bmp", (Vector2) Navmesh::MeshPointToWorldPoint((navPoint){5, 5}), 32, 32, 10);\
    Puddle puddle(r, (Vector2) Navmesh::MeshPointToWorldPoint((navPoint){5,10}));

    SDL_Event e;
    bool quit = false;

    float now = (float) SDL_GetPerformanceCounter();
    float last = 0.0f;
    double deltaTime = 0.0f;

    Navmesh mesh;
    mesh.blockCellAt(15, 10);

    while (!quit)
    {
        last = now;
        now = (float) SDL_GetPerformanceCounter();

        deltaTime = (double)((now - last) * 1000 / (double) SDL_GetPerformanceFrequency());
        deltaTime *= 0.001;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        // update
        emp.update(deltaTime, mesh);
        t.update(deltaTime);
        puddle.update(deltaTime);

        // draw
        r.clearScreen();

        emp.draw(r);
        wall.draw(r);
        t.draw(r);
        puddle.draw(r);

        r.present();

        SDL_UpdateWindowSurface(d.getHandle());
    }

    SDL_Quit();

    return 0;
}
