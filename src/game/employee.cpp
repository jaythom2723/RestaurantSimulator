#include "employee.h"

#include "dbg.h"
#include "aStar.h"

#include <SDL2/SDL.h>

#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace resimdbg;

std::pair<int, int> Employee::calcOrigin()
{
    return std::make_pair(x + (width / 2), y + (height / 2));
}

float Employee::calcDistanceToWaypoint()
{
    using namespace std;

    std::pair<int,int> o = calcOrigin();

    return sqrt(pow(curWaypoint.x - o.first, 2) + pow(curWaypoint.y - o.second, 2));
}

float Employee::calcAngleToWaypoint()
{
    using namespace std;

    std::pair<int, int> o = calcOrigin();

    return atan2(curWaypoint.y - o.second, curWaypoint.x - o.first);
}

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

        // TODO: Lerp;
        // x = curWaypoint.x;
        // y = curWaypoint.y;

        distToCurWaypoint = calcDistanceToWaypoint();
        angleToCurWaypoint = calcAngleToWaypoint();

        shouldMove = true;
    }

    if (shouldMove)
    {
        distToCurWaypoint = calcDistanceToWaypoint();
        angleToCurWaypoint = calcAngleToWaypoint();

        if (distToCurWaypoint <= 20.0f)
        {
            shouldMove = false;
            path.pop();

            if (path.empty())
            {
                // TODO: Lerp :P
                x = curWaypoint.x - (width / 2);
                y = curWaypoint.y - (height / 2);
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
}

int Employee::getId()
{
    return id;
}

std::stack<navPoint>& Employee::getPath()
{
    return path;
}

void Employee::choosePath(Navmesh& mesh)
{
    navPoint src = (navPoint){ x / 32, y / 30 };

    // TODO: have the employee determine their destination on their own
    navPoint dest = (navPoint){ 0 };
    dest.x = std::rand() % (Navmesh::COL - 1);
    dest.y = std::rand() % (Navmesh::ROW - 1);

    std::printf("%d, %d\n", dest.x, dest.y);

    aStarSearch(mesh, src, dest, &path);
}
