#include "Globals.h"
#include "World.h"

#include "Components.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "Engine/Engine/Window.h"
#include "Engine/Render/Render.h"

namespace FEngine
{
    World::World()
    {
        m_Registry = std::make_unique<entt::registry>();
        m_EntityFactory = std::make_unique<EntityFactory>();
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

    bool World::LoadFromFile(const Path& path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            return false;
        }

        std::string line;
        std::vector<std::string> currentLayer;
        std::string currentLayerName = "Default";
        int zIndex = 0;
        bool inLayer = false;
        bool firstLayer = true;

        while (std::getline(file, line))
        {
            // Trim whitespace from the line
            line.erase(0, line.find_first_not_of(" \t"));
            line.erase(line.find_last_not_of(" \t") + 1);

            // Skip empty lines
            if (line.empty()) continue;

            // Check if we're starting a new layer section
            if (line.find("---") == 0)
            {
                // Process the current layer if we have one
                if (inLayer && !currentLayer.empty())
                {
                    if (currentLayerName.find("Layer") != std::string::npos)
                    {
                        ProcessMapLayer(currentLayer, zIndex++);
                    }
                    else
                    {
                        ProcessObjectLayer(currentLayer, zIndex);
                    }
                    currentLayer.clear();
                }

                // Extract layer name
                size_t pos = line.find('#');
                if (pos != std::string::npos)
                {
                    currentLayerName = line.substr(pos + 1);
                    // Trim whitespace
                    currentLayerName.erase(0, currentLayerName.find_first_not_of(" \t"));
                    currentLayerName.erase(currentLayerName.find_last_not_of(" \t") + 1);
                }
                inLayer = true;
                firstLayer = false;
            }
            else if (firstLayer)
            {
                // Handle the first layer (before any --- markers)
                if (line[0] == '#')
                {
                    // This is a comment line, use it as layer name
                    currentLayerName = line.substr(1);
                    // Trim whitespace
                    currentLayerName.erase(0, currentLayerName.find_first_not_of(" \t"));
                    currentLayerName.erase(currentLayerName.find_last_not_of(" \t") + 1);
                }
                else
                {
                    // This is data for the first layer
                    currentLayer.push_back(line);
                    inLayer = true;
                }
            }
            else if (inLayer)
            {
                currentLayer.push_back(line);
            }
        }

        // Process the last layer
        if (inLayer && !currentLayer.empty())
        {
            if (currentLayerName.find("Layer") != std::string::npos)
            {
                ProcessMapLayer(currentLayer, zIndex++);
            }
            else
            {
                ProcessObjectLayer(currentLayer, zIndex);
            }
        }

        return true;
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

        // Update all systems
        for (auto& system : m_Systems)
        {
            system->OnTick(deltaTime);
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

        for (auto& system : m_Systems)
        {
            system->OnDraw();
        }

        RenderVisibleEntities();

        Render::EndRenderCamera();
    }

    Entity World::CreateEntity(const std::string& name)
    {
        Entity entity(m_Registry->create(), this);

        static uint32_t nextID = 0;
        entity.AddComponent<IdentificationComponent>(
            name.empty() ? "Entity_" + std::to_string(nextID) : name,
            true,
            nextID++
        );

        entity.AddComponent<TransformComponent>();

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

    EntityFactory& World::GetEntityFactory()
    {
        return *m_EntityFactory;
    }

    const EntityFactory& World::GetEntityFactory() const
    {
        return *m_EntityFactory;
    }

    Entity World::CreatePrefab(const std::string& prefabName, const Vector3& position)
    {
        auto it = m_Prefabs.find(prefabName);
        if (it == m_Prefabs.end())
        {
            Logger::Log(Logger::ELogType::Error, "Unknown prefab: " + prefabName);
            return Entity{ entt::null, nullptr };
        }

        Entity entity = CreateEntity(prefabName);
        entity.GetComponent<TransformComponent>().Position = position;

        // Apply prefab configuration
        it->second(entity);

        return entity;
    }

    void World::RegisterPrefab(const std::string& prefabName, std::function<void(Entity)> setupFunction)
    {
        m_Prefabs[prefabName] = std::move(setupFunction);
    }

    void World::ProcessMapLayer(const std::vector<std::string>& layerData, int zIndex)
    {
        for (size_t y = 0; y < layerData.size(); y++)
        {
            const std::string& row = layerData[y];
            for (size_t x = 0; x < row.size(); x++)
            {
                char symbol = row[x];
                if (symbol == ' ') continue;

                if (m_EntityFactory->HasCreator(symbol))
                {
                    Vector3 position(static_cast<float>(x) * TILE_SIZE,
                        static_cast<float>(y) * TILE_SIZE, 0.0f);
                    Entity entity = m_EntityFactory->CreateEntity(this, symbol, position);

                    if (!entity.IsNull() && entity.HasComponent<RenderComponent>())
                    {
                        entity.GetComponent<RenderComponent>().ZOrder = zIndex;
                    }
                }
            }
        }
    }

    void World::ProcessObjectLayer(const std::vector<std::string>& layerData, int zIndex)
    {
       ProcessMapLayer(layerData, zIndex);
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
