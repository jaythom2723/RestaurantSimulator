#include "employee.h"

#include "dbg.h"
#include "aStar.h"

#include "common.h"

#include <ctime>

Employee::Employee(Renderer& r, int id, Vector2 pos, float speed)
    : Actor(r, "res/employee.bmp", pos, 32, 32, speed)
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

}

void Employee::update(double deltaTime)
{
    using namespace std;

    getNextWaypoint();
    moveTowardsWaypoint(deltaTime);
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
