#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED

#include "common.h"

#include "renderer.h"
#include "entity.h"
#include "texture.h"
#include "navmesh.h"
#include "actor.h"
#include "task.h"

#include <memory>
#include <vector>

class Employee : public Actor
{
private:
    int empId;

    std::shared_ptr<Task> task;
    std::vector<TaskClass> allowedTasks;

public:
    Employee(Renderer& r, int empId, Vector2 pos, float speed);
    ~Employee();

    void update(double deltaTime);
    void draw(Renderer& r);

    int getEmpId();
    const std::stack<navPoint>& getPath();
};

#endif // EMPLOYEE_H_INCLUDED
