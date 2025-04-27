#include "engine.h"

std::vector<Entity*> EngineState::entities;
std::map<TaskClass, std::stack<std::shared_ptr<Task>>*> EngineState::tasks;
Navmesh EngineState::mesh;

double EngineState::GetDT(float *now, float *last)
{
    (*last) = (*now);
    (*now) = SDL_GetPerformanceCounter();

    return (double)((((*now) - (*last)) * 1000 / (double) SDL_GetPerformanceFrequency()) * 0.001);
}
