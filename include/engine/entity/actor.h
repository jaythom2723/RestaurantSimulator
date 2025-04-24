#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED

// actors are the entities that can roam around the navmesh

#include "common.h"

#include "vector.h"
#include "texturedentity.h"
#include "navmesh.h"

class Actor : public TexturedEntity
{
private:

protected:
    float speed;

    std::stack<navPoint> path;
    navPoint curWaypoint;
    float distToCurWaypoint;
    float angleToCurWaypoint;

    bool shouldMove;

    float calcDistanceToWaypoint();
    float calcAngleToWaypoint();

    void getNextWaypoint();
    void moveTowardsWaypoint(double deltaTime);

public:
    Actor(Renderer& r, std::string path, Vector2 pos, int width, int height, float speed);
    virtual ~Actor();

    void choosePath(Navmesh& mesh);
};

#endif // ACTOR_H_INCLUDED
