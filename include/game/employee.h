#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED

#include "renderer.h"
#include "entity.h"
#include "texture.h"

class Employee : public Entity
{
private:
    int id;

protected:
    Texture *texture;

public:
    Employee(Renderer& r, int id, int x, int y);
    ~Employee();

    void update(float deltaTime);
    void draw(Renderer& r);

    int getId();
};

#endif // EMPLOYEE_H_INCLUDED
