#pragma once

namespace FEngine
{
    class World;

    class ISystem
    {
    public:
        virtual ~ISystem() = default;
        virtual void OnTick(float deltaTime) = 0;
        virtual void OnDraw() const {} // Optional draw method

        // Called when system is added to world
        virtual void OnAddedToWorld(World* world) { m_World = world; }

    protected:
        World* m_World = nullptr;
    };
}//namespace FEngine