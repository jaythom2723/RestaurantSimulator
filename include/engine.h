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
    static std::vector<std::unique_ptr<Entity>> entities;
    static std::map<TaskClass, std::stack<std::shared_ptr<Task>>*> tasks;
    static Navmesh mesh;

    template<typename T, typename... Args>
    static void SpawnEntity(Args&&... args)
    {
        entities.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    }

    template<typename T>
    static void SpawnEntity(T *ent)
    {
        entities.push_back(std::make_unique(ent));
    }

    template<typename T>
    static void DestroyEntity(T *ent)
    {
        auto it = EngineState::entities.begin() + ent->getId();
        EngineState::entities.erase(it);
        EngineState::entities.shrink_to_fit();
    }

    static double GetDT(float *now, float *last);
};

#endif // ENGINE_H_INCLUDED
