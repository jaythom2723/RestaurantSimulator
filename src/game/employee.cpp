#include "employee.h"

#include "dbg.h"

#include <SDL2/SDL.h>

#include <cmath>

using namespace resimdbg;

Employee::Employee(Renderer& r, int id, int x, int y) : Entity(x, y, 32, 32)
{
    this->id = id;

    texture = new Texture(r, "res/employee.bmp");
}

Employee::~Employee()
{
    delete texture;
}

void Employee::update(float deltaTime)
{
    if (!path.empty() && !shouldMove)
    {
        curWaypoint = path.top();
        shouldMove = true;
    }

    while (shouldMove && !path.empty())
    {
        int scaledX, scaledY;
        float angle, dist;

        scaledX = 16 + (32 * curWaypoint.x);
        scaledY = 15 + (30 * curWaypoint.y);

        angle = std::atan2(scaledY - y, scaledX - x);
        dist = std::sqrt(std::pow(scaledX - x, 2) + std::pow(scaledY - y, 2));

        x += std::cos(angle) * speed * deltaTime;
        y += std::sin(angle) * speed * deltaTime;

        if (dist <= 10)
        {
            curWaypoint = (navPoint){ -1, -1 };
            shouldMove = false;
            path.pop();
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
