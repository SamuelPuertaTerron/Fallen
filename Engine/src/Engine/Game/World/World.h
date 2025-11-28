#pragma once
#include "WorldJsonSerialization.h"
#include "entt/entt.hpp"

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

        void Tick(float deltaTime);
        void Draw() const;

        [[nodiscard]] Entity GetEntityFromName(const std::string& name);

        [[nodiscard]] std::vector<Entity> GetEntities() const;

    	// Entity creation
        Entity CreateEntity(const std::string& name = "");
        void DestroyEntity(Entity& entity) const;

        void SaveWorld(const Path& path);

    private:
        std::pair<std::optional<Camera2DComponent>, std::optional<TransformComponent>> FindActiveCamera() const;
        void RenderVisibleEntities() const;

        Entity GetEntityFromEntt(entt::entity entity);
    private:
        std::unique_ptr<entt::registry> m_Registry = nullptr;

    	std::vector<Entity> m_Entities;

        WorldJsonSerialization m_WorldJsonSerialization;

        const float TILE_SIZE = 32.0f;
    };
}
