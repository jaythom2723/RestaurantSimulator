#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "common.h"

#include "display.h"
#include "renderer.h"
#include "navmesh.h"
#include "task.h"
#include "entity.h"

#include <map>
#include <memory>
#include <vector>
#include <utility>
#include <algorithm>

struct EngineState
{
    static std::vector<Entity*> entities;
    static std::map<TaskClass, std::stack<std::shared_ptr<Task>>*> tasks;
    static Navmesh mesh;

    template<typename T, typename... Args>
    static void SpawnEntity(Args&&... args)
    {
        entities.push_back(new T(std::forward<Args>(args)...));
    }

    template<typename T>
    static void SpawnEntity(T *ent)
    {
        entities.push_back(ent);
    }

    template<typename T>
    static void DestroyEntity(T *ent)
    {
        auto it = std::find(EngineState::entities.begin(), EngineState::entities.end(), ent);
        if (it == EngineState::entities.end())
            return;

        delete ent;
        EngineState::entities.erase(it);
    }

    static double GetDT(float *now, float *last);
};

#endif // ENGINE_H_INCLUDED
