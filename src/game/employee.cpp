#include "employee.h"

#include "dbg.h"

#include <SDL2/SDL.h>

#include <cmath>

using namespace resimdbg;

Employee::Employee(Renderer& r, int id, int x, int y) : Entity(x, y, 32, 32)
{
    this->id = id;

    texture = new Texture(r, "res/employee.bmp");

    curWaypoint = (navPoint){-1,-1};
    distToCurWaypoint = 0.0f;
    angleToCurWaypoint = 0.0f;

    shouldMove = false;
}

Employee::~Employee()
{
    delete texture;
}

void Employee::update(double deltaTime)
{
    using namespace std;

    if (!path.empty() && !shouldMove)
    {
        curWaypoint.x = 16 + (32 * path.top().x);
        curWaypoint.y = 15 + (30 * path.top().y);

        distToCurWaypoint = sqrt(pow(curWaypoint.x - x, 2) + pow(curWaypoint.y - y, 2));
        angleToCurWaypoint = atan2(curWaypoint.y - y, curWaypoint.x - x);

        shouldMove = true;

        printf("New waypoint! -> (%d, %d)\n", curWaypoint.x, curWaypoint.y);
    }

    if (shouldMove)
    {
        distToCurWaypoint = sqrt(pow(curWaypoint.x - x, 2) + pow(curWaypoint.y - y, 2));

        if (distToCurWaypoint <= 20.0f)
        {
            shouldMove = false;
            path.pop();

            printf("Arrived at waypoint! -> (%d, %d)\n", curWaypoint.x, curWaypoint.y);

            if (path.empty())
            {
                printf("Arrived at destination!\n");
            }
        } else
        {
            x += (cos(angleToCurWaypoint) * speed) * deltaTime;
            y += (sin(angleToCurWaypoint) * speed) * deltaTime;
        }
    }
}

void Employee::draw(Renderer& r)
{
    SDL_Rect rect = {0};
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    r.texCopy(texture->getTexture(), nullptr, &rect);

    if (curWaypoint.x != -1 && curWaypoint.y != -1)
    {
        SDL_Rect pointRect = {0};
        pointRect.w = 4;
        pointRect.h = 4;
        pointRect.x = curWaypoint.x - (pointRect.w / 2);
        pointRect.y = curWaypoint.y - (pointRect.h / 2);

        SDL_SetRenderDrawColor(r.getHandle(), 0xff, 0x00, 0x00, 0xff);
        SDL_RenderFillRect(r.getHandle(), &pointRect);
    }
}

int Employee::getId()
{
    return id;
}

std::stack<navPoint>& Employee::getPath()
{
    return path;
}

void Employee::setPath(std::stack<navPoint> path)
{
    this->path = path;
}
