#include "FallenGlobals.h"
#include "GameSerialization.h"

#include "nlohmann/json.hpp"

namespace Fallen
{
	void GameSerialization::SerializeData(Json& out)
	{
		Logger::Log(Logger::ELogType::Debug, "Saved Game World");

		Entity entity = m_pWorld->GetEntityFromName("Player");

		out["Entity"]["Name"] = entity.GetName();
		out["Entity"]["ID"] = entity.GetID().ID;
		out["Entity"]["Components"]["Transform"]["X"] = entity.GetTransform().Position.X;
		out["Entity"]["Components"]["Transform"]["Y"] = entity.GetTransform().Position.Y;
	}

	void GameSerialization::DeserializeData(const Json& in)
	{
		Entity entity = m_pWorld->GetEntityFromName("Player");

		TransformComponent& comp = entity.GetTransform();

		comp.Position.X = in["Entity"]["Components"]["Transform"]["X"];
		comp.Position.Y = in["Entity"]["Components"]["Transform"]["Y"];

		entity.GetComponent<TransformComponent>() = comp;
	}
}//namespace Fallen