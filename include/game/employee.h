#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED

#include "renderer.h"
#include "entity.h"
#include "texture.h"
#include "navmesh.h"

#include <stack>

class Employee : public Entity
{
private:
    int id;
    std::stack<navPoint> path;
    float speed = 150;

    navPoint curWaypoint;
    float distToCurWaypoint;
    float angleToCurWaypoint;

    bool shouldMove;

protected:
    Texture *texture;

public:
    Employee(Renderer& r, int id, int x, int y);
    ~Employee();

    void update(double deltaTime);
    void draw(Renderer& r);

    int getId();
    std::stack<navPoint>& getPath();
    void setPath(std::stack<navPoint> path);
};

#endif // EMPLOYEE_H_INCLUDED
