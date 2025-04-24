#include "employee.h"

#include "dbg.h"
#include "aStar.h"

#include <SDL2/SDL.h>

#include <cmath>
#include <ctime>
#include <cstdlib>

float Employee::calcDistanceToWaypoint()
{
    using namespace std;

    Vector2 o = calcOrigin();

    return sqrt(pow(curWaypoint.x - o.x, 2) + pow(curWaypoint.y - o.y, 2));
}

float Employee::calcAngleToWaypoint()
{
    using namespace std;

    Vector2 o = calcOrigin();

    return atan2(curWaypoint.y - o.y, curWaypoint.x - o.x);
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

        if (distToCurWaypoint <= 10.0f)
        {
            shouldMove = false;
            path.pop();

            if (path.empty())
            {
                // TODO: Lerp :P
                pos.x = curWaypoint.x - (width / 2);
                pos.y = curWaypoint.y - (height / 2);
            }
        } else
        {
            pos.x += (cos(angleToCurWaypoint) * speed) * deltaTime;
            pos.y += (sin(angleToCurWaypoint) * speed) * deltaTime;
        }
    }
}

void Employee::draw(Renderer& r)
{
    SDL_Rect rect = {0};
    rect.x = pos.x;
    rect.y = pos.y;
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
    navPoint src = (navPoint){ pos.x / 32, pos.y / 30 };

    // TODO: have the employee determine their destination on their own
    navPoint dest = (navPoint){ 0 };
    dest.x = std::rand() % (Navmesh::COL - 1);
    dest.y = std::rand() % (Navmesh::ROW - 1);

    std::printf("%d, %d\n", dest.x, dest.y);

    aStarSearch(mesh, src, dest, &path);
}
