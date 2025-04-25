#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED

#include "common.h"

#include "renderer.h"
#include "entity.h"
#include "texture.h"
#include "navmesh.h"
#include "actor.h"
#include "task.h"

class Employee : public Actor
{
private:
    int id;
    Task *task = nullptr;

public:
    Employee(Renderer& r, int id, Vector2 pos, float speed);
    ~Employee();

    void update(double deltaTime, Navmesh& mesh);
    void draw(Renderer& r);

    int getId();
    const std::stack<navPoint>& getPath();
};

#endif // EMPLOYEE_H_INCLUDED
