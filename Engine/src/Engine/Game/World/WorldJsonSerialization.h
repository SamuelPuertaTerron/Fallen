#pragma once

namespace FEngine
{
	class Entity;
	class World;

	class WorldJsonSerialization : public IJsonSerialization
	{
	public:
		WorldJsonSerialization() = default;
		WorldJsonSerialization(World* world)
			: m_pWorld(world) {}

		~WorldJsonSerialization() override = default;

		void SerializeData(Json& out) override;
		void DeserializeData(const Json& in) override;

		void SaveEntity(Json& out, Entity& entity);

	private:
		World* m_pWorld;
	};
}//namespace FEngine