#include "Globals.h"
#include "WorldJsonSerialization.h"

#include "Engine/Game/World/World.h"
#include "Engine/Game/World/Entity.h"

#include "nlohmann/json.hpp"

namespace FEngine
{
	void WorldJsonSerialization::SerializeData(Json& out)
	{
		for (Entity& entity : m_pWorld->GetEntities())
		{
			SaveEntity(out, entity);
		}
	}

	void WorldJsonSerialization::DeserializeData(const Json& in)
	{
		Entity entity = m_pWorld->CreateEntity();
	}

	void WorldJsonSerialization::SaveEntity(Json& out, Entity& entity)
	{
		out["World"]["Entity " + entity.GetName()];
		out["World"]["Entity " + entity.GetName()]["ID"] = entity.GetID().ID;

		out["World"]["Entity " + entity.GetName()]["Components"]["Transform"]["X"] = entity.GetTransform().Position.X;
		out["World"]["Entity " + entity.GetName()]["Components"]["Transform"]["Y"] = entity.GetTransform().Position.Y;
	}
}//namespace FEngine