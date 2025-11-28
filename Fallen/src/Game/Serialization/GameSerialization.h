#pragma once

namespace Fallen
{
	class GameSerialization : public IJsonSerialization
	{
	public:
		GameSerialization(World* world)
			: m_pWorld(world) {}
		~GameSerialization() override = default;

		void SerializeData(Json& out) override;
		void DeserializeData(const Json& in) override;

	private:
		World* m_pWorld;
	};
}//namespace Fallen