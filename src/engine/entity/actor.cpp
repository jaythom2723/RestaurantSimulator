#include "actor.h"

#include "aStar.h"

Actor::Actor(Renderer& r, std::string path, Vector2 pos, int width, int height, float speed)
    : TexturedEntity(r, path, pos, width, height)
{
    this->speed = speed;

    shouldMove = false;

    distToCurWaypoint = 0.0f;
    angleToCurWaypoint = 0.0f;
    curWaypoint.x = -1;
    curWaypoint.y = -1;
}

Actor::~Actor()
{

}

float Actor::calcDistanceToWaypoint()
{
    using namespace std;
    Vector2 o = calcOrigin();
    return sqrt(pow(curWaypoint.x - o.x, 2) + pow(curWaypoint.y - o.y, 2));
}

float Actor::calcAngleToWaypoint()
{
    using namespace std;
    Vector2 o = calcOrigin();
    return atan2(curWaypoint.y - o.y, curWaypoint.x - o.x);
}

void Actor::getNextWaypoint()
{
    if (!path.empty() && !shouldMove)
    {
        // scaling from mesh point to world point
        curWaypoint = Navmesh::MeshPointToWorldPoint(path.top());

        distToCurWaypoint = calcDistanceToWaypoint();
        angleToCurWaypoint = calcAngleToWaypoint();

        shouldMove = true;
    }
}

void Actor::moveTowardsWaypoint(double deltaTime)
{
    if (!shouldMove)
        return;

    distToCurWaypoint = calcDistanceToWaypoint();
    angleToCurWaypoint = calcAngleToWaypoint();

    if (distToCurWaypoint <= 10.0f)
    {
        shouldMove = false;
        path.pop();

        if (path.empty())
        {
            pos.x = curWaypoint.x - (width / 2);
            pos.y = curWaypoint.y - (height / 2);
        }
        return;
    }

    pos.x += (std::cos(angleToCurWaypoint) * speed) * deltaTime;
    pos.y += (std::sin(angleToCurWaypoint) * speed) * deltaTime;
}

void Actor::choosePath(Navmesh& mesh, navPoint dest)
{
    navPoint src = Navmesh::Vector2ToMeshPoint(pos);
    aStarSearch(mesh, src, dest, &path);
}
