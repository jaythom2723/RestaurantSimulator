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

int main(int argc, char *argv[])
{
    using namespace resimdbg;

    if(pushErrorCheck(ERRTYPE_FAIL_INIT_SDL, SDL_Init(SDL_INIT_VIDEO) < 0))
        return -2;

    Display d("Test Window", 800, 600);
    Renderer r(d.getHandle());

    Employee emp(r, 0, 100, 100);
    Employee emp2(r, 1, 132, 100);
    Employee emp3(r, 2, 164, 100);
    Employee emp4(r, 3, 196, 100);

    SDL_Event e;
    bool quit = false;

    float now = (float) SDL_GetPerformanceCounter();
    float last = 0.0f;
    float deltaTime = 0.0f;

    Navmesh mesh;
    navPoint src = { (emp.getX() / 30), (emp.getY() / 32) };
    navPoint dest = { 15, 15 };
    std::stack<navPoint> path;
    aStarSearch(mesh, src, dest, &path);
    emp.setPath(path);

    while(!quit)
    {
        last = now;
        now = (float) SDL_GetPerformanceCounter();

        deltaTime = (float)((now - last) * 1000 / (float) SDL_GetPerformanceFrequency());
        deltaTime *= 0.001;

        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                quit = true;

            /*
            if (e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                case SDLK_SPACE:
                    aStarTest(r);
                    break;
                }
            }
            */
        }

        // update
        emp.update(deltaTime);

        // draw
        r.clearScreen();

        emp.draw(r);
        emp2.draw(r);
        emp3.draw(r);
        emp4.draw(r);

        /*
            Drawing the navmesh's vertices

                    int i,j;
        for (i = 0; i < 20; i++)
        {
            for (j = 0; j < 25; j++)
            {
                SDL_SetRenderDrawColor(r.getHandle(), 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderDrawPoint(r.getHandle(), 16 + (32 * j), 15 + (30 * i));
            }
        }

        */

        r.present();

        SDL_UpdateWindowSurface(d.getHandle());

        SDL_Delay(1000);
    }

    SDL_Quit();

    return 0;
}
