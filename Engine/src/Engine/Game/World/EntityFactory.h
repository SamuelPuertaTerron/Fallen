#pragma once
#include "Entity.h"

namespace FEngine
{
    class World;

    class EntityFactory
    {
    public:
        using EntityCreator = std::function<Entity(World*, const Vector3& position)>;

        EntityFactory() = default;
        ~EntityFactory() = default;

        void RegisterCreator(char symbol, EntityCreator creator);

        Entity CreateEntity(World* world, char symbol, const Vector3& position);

        bool HasCreator(char symbol) const;

    private:
        std::unordered_map<char, EntityCreator> m_Creators;
    };
}//namespace FEngine