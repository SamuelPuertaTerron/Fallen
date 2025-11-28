#pragma once
#include "Framework/IState.h"
#include "Game/Serialization/GameSerialization.h"

namespace Fallen
{
	class GameState : public IState
	{
	public:
		GameState() = default;
		~GameState() override = default;

		void OnCreate() override;
		void OnTick(float deltaTime) override;
		void OnRender() override;
		void OnDestroy() override;

	private:
		Entity CreateGrass(World* world, const FEngine::Vector3& position) const;
		Entity CreateDirt(World* world, const FEngine::Vector3& position) const;
		Entity CreatePlayer(World* world, const FEngine::Vector3& position);

		void OnKeyPress(EKeyCode code);
	private:
		std::shared_ptr<World> m_World = nullptr;

		ListenerHandle m_KeyPressHandle;

		GameSerialization* m_GameSerialization;
	};
}//namespace Fallen