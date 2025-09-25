#pragma once
#include "World.h"
#include "Components.h"

namespace FEngine
{
	class World;

	class Entity
	{
	public:
		Entity(entt::entity entity, World* world)
			: m_BaseEntity(entity), m_pWorld(world) {}

		~Entity()
		{
			//delete m_pWorld;
		}

		[[nodiscard]] IdentificationComponent& GetID()   { return GetComponent<IdentificationComponent>(); }
		[[nodiscard]] TransformComponent& GetTransform() { return GetComponent<TransformComponent>(); }

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return m_pWorld->GetRegistry().emplace<T>(m_BaseEntity, std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent() const
		{
			if (!HasComponent<T>())
			{
				return;
			}

			m_pWorld->GetRegistry().remove<T>(m_BaseEntity);
		}

		template<typename T>
		T& GetComponent()
		{
			ASSERT(HasComponent<T>(), "Cannot get component on entity as it does not exist");

			return m_pWorld->GetRegistry().get<T>(m_BaseEntity);
		}

		template<typename T>
		[[nodiscard]] bool HasComponent() const
		{
			return m_pWorld->GetRegistry().all_of<T>(m_BaseEntity);
		}

		[[nodiscard]] bool IsNull() const
		{
			return m_BaseEntity == entt::null || m_pWorld == nullptr;
		}

		[[nodiscard]] entt::entity GetBaseEntity() const
		{
			return m_BaseEntity;
		}

	private:
		entt::entity m_BaseEntity;
		World* m_pWorld = nullptr;
	};	
}//namespace FEngine