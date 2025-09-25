#pragma once
#include "entt/entt.hpp"
#include "ISystem.h"

namespace FEngine
{
	struct TransformComponent;
	struct Camera2DComponent;
	class EntityFactory;
	class Entity;
	class Texture;

    class World
    {
    public:
        World();
        ~World();

        [[nodiscard]] entt::registry& GetRegistry() const { return *m_Registry; }

        bool LoadFromFile(const Path& path);
        void Tick(float deltaTime);
        void Draw() const;

        template<typename T, typename... Args>
        T* AddSystem(Args&&... args)
        {
            static_assert(std::is_base_of_v<ISystem, T>, "System must inherit from ISystem");
            auto system = std::make_unique<T>(std::forward<Args>(args)...);
            T* ptr = system.get();
            system->OnAddedToWorld(this);
            m_Systems.push_back(std::move(system));
            return ptr;
        }

        template<typename T>
        T* GetSystem()
        {
            for (auto& system : m_Systems)
            {
                if (auto ptr = dynamic_cast<T*>(system.get()))
                    return ptr;
            }
            return nullptr;
        }

        // Entity creation
        Entity CreateEntity(const std::string& name = "");
        void DestroyEntity(Entity& entity) const;

        // Factory access
        EntityFactory& GetEntityFactory();
        const EntityFactory& GetEntityFactory() const;

        // Prefabs - create entities from predefined templates
        Entity CreatePrefab(const std::string& prefabName, const Vector3& position);
        void RegisterPrefab(const std::string& prefabName, std::function<void(Entity)> setupFunction);
    private:
        void ProcessMapLayer(const std::vector<std::string>& layerData, int zIndex);
        void ProcessObjectLayer(const std::vector<std::string>& layerData, int zIndex);

        std::pair<std::optional<Camera2DComponent>, std::optional<TransformComponent>> FindActiveCamera() const;
        void RenderVisibleEntities() const;

        Entity GetEntityFromEntt(entt::entity entity);
    private:
        std::unique_ptr<entt::registry> m_Registry = nullptr;
        std::unique_ptr<EntityFactory> m_EntityFactory = nullptr;

        std::vector<std::unique_ptr<ISystem>> m_Systems;
    	std::vector<Entity> m_Entities;
        std::unordered_map<std::string, std::function<void(Entity)>> m_Prefabs;

        const float TILE_SIZE = 32.0f;
    };
}
