#include "Globals.h"
#include "EntityFactory.h"

namespace FEngine
{
	void EntityFactory::RegisterCreator(char symbol, EntityCreator creator)
	{
		m_Creators[symbol] = std::move(creator);
	}
	Entity EntityFactory::CreateEntity(World* world, char symbol, const Vector3& position)
	{
		auto it = m_Creators.find(symbol);
		if (it != m_Creators.end())
		{
			return it->second(world, position);
		}
		return { entt::null, world }; // Invalid entity
	}

	bool EntityFactory::HasCreator(char symbol) const
	{
		return m_Creators.contains(symbol);
	}
}//namespace FEngine