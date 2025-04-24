#include <iostream>

#include <SDL2/SDL.h>

#include "dbg.h"
#include "display.h"
#include "renderer.h"
#include "texture.h"
#include "entity.h"
#include "transform.h"
#include "employee.h"

#include "aStar.h"

void testAStar(Navmesh& mesh, Employee& emp);

int main(int argc, char *argv[])
{
    using namespace resimdbg;

    if(pushErrorCheck(ERRTYPE_FAIL_INIT_SDL, SDL_Init(SDL_INIT_VIDEO) < 0))
        return -2;

    Display d("Test Window", 800, 600);
    Renderer r(d.getHandle());

    Employee emp(r, 0, 100, 100);

    SDL_Event e;
    bool quit = false;

    float now = (float) SDL_GetPerformanceCounter();
    float last = 0.0f;
    double deltaTime = 0.0f;

    Navmesh mesh;

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
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_SPACE:
                    while (emp.getPath().empty())
                    {
                        emp.choosePath(mesh);
                    }
                    break;
                }
            }
        }

        // update
        emp.update(deltaTime);

        // draw
        r.clearScreen();

        int row,col;
        for (row = 0; row < Navmesh::ROW; row++)
        {
            for (col = 0; col < Navmesh::COL; col++)
            {
                if (mesh.getCellAt(row, col) == GSPOT_OPEN)
                {
                    SDL_SetRenderDrawColor(r.getHandle(), 0xff, 0xff, 0xff, 0xff);
                    SDL_RenderDrawPoint(r.getHandle(), 16 + (32 * col), 15 + (30 * row));
                }
            }
        }

        emp.draw(r);

        r.present();

        SDL_UpdateWindowSurface(d.getHandle());
    }

    SDL_Quit();

    return 0;
}
