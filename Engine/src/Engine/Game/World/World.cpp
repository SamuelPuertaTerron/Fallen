#include "Globals.h"
#include "World.h"

#include "Components.h"
#include "Entity.h"
#include "Engine/Engine/Window.h"
#include "Engine/Render/Render.h"

namespace FEngine
{
    World::World()
    {
        m_Registry = std::make_unique<entt::registry>();
        m_WorldJsonSerialization = WorldJsonSerialization{ this };
    }

    World::~World()
    {
        auto view = m_Registry->view<ScriptComponent>();
        for (auto entity : view)
        {
            auto& script = view.get<ScriptComponent>(entity);
            if (script.OnDestroy)
            {
                Entity e(entity, this);
                script.OnDestroy(e);
            }
        }
    }

    void World::Tick(float deltaTime)
    {
        // Update script components
        auto scriptView = m_Registry->view<ScriptComponent>();
        for (auto entity : scriptView)
        {
            auto& script = scriptView.get<ScriptComponent>(entity);
            if (script.OnTick)
            {
                Entity e(entity, this);
                script.OnTick(e, deltaTime);
            }
        }
    }

    void World::Draw() const
    {
        auto [camera, cameraTransform] = FindActiveCamera();
        if (!camera.has_value() || !cameraTransform.has_value())
        {
            Logger::Log(Logger::ELogType::Warning, "No active camera found for rendering");
            Render::DrawText("No active camera found for rendering", Window::GetCenter(), EFontAlignment::Center);

            return;
        }

        Render::BeginRenderCamera(camera.value(), cameraTransform.value());

        auto view = m_Registry->view<TransformComponent, RenderComponent>();
        for (auto entity : view)
        {
            const TransformComponent& transform = m_Registry->get<TransformComponent>(entity);
            const RenderComponent& render = m_Registry->get<RenderComponent>(entity);
            Render::DrawTexture(render.Texture, transform.Position, render.Colour);
        }

        Render::EndRenderCamera();
    }

    Entity World::GetEntityFromName(const std::string& name)
    {
        for (Entity e : m_Entities)
        {
            if (e.GetName() == name)
            {
                return e;
            }
        }

        return { entt::null, nullptr };
    }

    std::vector<Entity> World::GetEntities() const
    {
        return m_Entities;
    }

    Entity World::CreateEntity(const std::string& name)
    {
        Entity entity(m_Registry->create(), this);

        static uint32_t nextID = 0;
        entity.AddComponent<IdentificationComponent>(
            name.empty() ? "Entity_" + std::to_string(nextID) : name,
            true,
            Random::Range(10000, 1000000)
        );

        m_Entities.push_back(entity);
        return entity;
    }

    void World::DestroyEntity(Entity& entity) const
    {
        if (entity.IsNull()) return;

        // Call OnDestroy if exists
        if (entity.HasComponent<ScriptComponent>())
        {
            auto& script = entity.GetComponent<ScriptComponent>();
            if (script.OnDestroy)
            {
                script.OnDestroy(entity);
            }
        }

        m_Registry->destroy(entity.GetBaseEntity());
    }

    void World::SaveWorld(const Path& path)
    {
        JsonSerializer::SerializeObject(path, m_WorldJsonSerialization);
    }

	std::pair<std::optional<Camera2DComponent>, std::optional<TransformComponent>> World::FindActiveCamera() const
    {
        auto cameraView = m_Registry->view<Camera2DComponent, TransformComponent>();
        for (auto entity : cameraView)
        {
            const auto& camera = cameraView.get<Camera2DComponent>(entity);

            if (camera.IsMainCamera)
            {
                return
		     {
                    camera,
                    cameraView.get<TransformComponent>(entity)
                };
            }
        }

        return { std::nullopt, std::nullopt };
    }

    void World::RenderVisibleEntities() const
    {
        // Get all entities with both Transform and Render components
        auto view = m_Registry->view<const TransformComponent, const RenderComponent>();

        // Group entities by render layer
        std::array<std::vector<entt::entity>, 6> renderLayers;

        // Populate render layers
        for (auto entity : view)
        {
            const auto& render = view.get<const RenderComponent>(entity);

            if (!render.IsVisible) continue;

            size_t layerIndex = static_cast<size_t>(render.RenderLayer);
            if (layerIndex < renderLayers.size())
            {
                renderLayers[layerIndex].push_back(entity);
            }
        }

        // For each layer, sort entities by ZOrder
        for (auto& layer : renderLayers)
        {
            // Sort using a lambda that compares ZOrder
            std::sort(layer.begin(), layer.end(), [this](entt::entity a, entt::entity b) {
                const auto& renderA = m_Registry->get<const RenderComponent>(a);
                const auto& renderB = m_Registry->get<const RenderComponent>(b);
                return renderA.ZOrder < renderB.ZOrder;
                });

            // Render entities in this layer
            for (auto entity : layer)
            {
                const auto& transform = m_Registry->get<const TransformComponent>(entity);
                const auto& render = m_Registry->get<const RenderComponent>(entity);
                Render::DrawTexture(render.Texture, transform.Position, render.Colour);
            }
        }
    }

    Entity World::GetEntityFromEntt(entt::entity entity)
    {
	    for (Entity e : m_Entities)
	    {
		    if (e.GetBaseEntity() == entity)
		    {
                return e;
		    }
	    }

        return {entt::null, nullptr};
    }
}
