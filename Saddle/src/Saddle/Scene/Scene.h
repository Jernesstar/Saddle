#pragma once

#include <iostream>
#include <vector>
#include <functional>

#include "Saddle/Core/Time.h"

namespace Saddle {

class Entity;

class Scene {
public:
    Scene();
    ~Scene();

    // Entity& GetEntityByUUID(UUID entity_ID);
    
    void Update();
    void Render();
    void Pause();

    void AddEntity(Entity& entity);

    std::vector<Entity*> Query(std::function<bool(const Entity& entity)> predicate);

private:
    std::vector<Entity*> entities;
    TimePoint m_LastFrameTime;
};

}