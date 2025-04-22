#include "employee.h"

#include "dbg.h"

#include <SDL2/SDL.h>

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

}

void Employee::draw(Renderer& r)
{
    SDL_Rect rect = {0};
    rect.x = tform.x;
    rect.y = tform.y;
    rect.w = tform.w;
    rect.h = tform.h;

    r.texCopy(texture->getTexture(), nullptr, &rect);
}

int Employee::getId()
{
    return id;
}
