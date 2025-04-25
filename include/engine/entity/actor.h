#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED

// actors are the entities that can roam around the navmesh

#include "common.h"

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

    virtual void update(double deltaTime, Navmesh& mesh) {}
    virtual void draw(Renderer& r) {}

    void choosePath(Navmesh& mesh, navPoint dest);
};

#endif // ACTOR_H_INCLUDED
