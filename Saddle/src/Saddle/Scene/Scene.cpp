#include "Scene.h"
#include "Entity.h"

#include "Saddle/Renderer/Renderer.h"
#include "Saddle/Systems/EventListenerSystem.h"

namespace Saddle {

Scene::Scene() : entities() { }
Scene::~Scene() { }

void Scene::OnUpdate()
{
    float time = TimeStep::GetTime();
    TimeStep ts = time - m_LastFrameTime;
    m_LastFrameTime = time;
    
    for(int i = 0; i < entities.size(); i++)
    {
        Entity& entity = *entities.at(i);
    }
}

void Scene::OnSceneRender()
{
    for(int i = 0; i < entities.size(); i++)
    {
        Entity& entity = *entities.at(i);
        if(entity.HasComponent<TextureComponent>())
        {
            auto& coordinate = entity.GetComponent<Coordinate2DComponent>().Coordinate2D;
            auto& rect = entity.GetComponent<RectComponent>().Rect;
            auto& texture = entity.GetComponent<TextureComponent>().texture;
            Renderer::DrawTexture(texture, coordinate, rect);
        }
    }
    Renderer::Render();
}

void Scene::AddEntity(Entity& entity)
{
    entities.push_back(&entity);

    // Note: Place this in a method that regularly updates all the Entities
    if(entity.HasComponent<EventListenerComponent>())
    {
        EventDispatcher::RegisterEventListener<Event>(
            [&entity](Event& event) {
                EventListenerSystem::OnEvent(entity, event);
            }
        );
    }
}

std::vector<Entity*> Scene::Query(std::function<bool(const Entity& entity)> predicate)
{
    std::vector<Entity*> result = { };
    for(int i = 0; i < entities.size(); i++)
    {
        Entity& entity = *entities.at(i);
        if(predicate(entity))
        {
            result.push_back(&entity);
        }
    }
    return result;
}

}