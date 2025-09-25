#pragma once
#include "Framework/IState.h"

namespace Fallen
{
	class GameState : public IState
	{
	public:
		GameState();
		~GameState() override = default;

		void OnCreate() override;
		void OnTick(float deltaTime) override;
		void OnRender() override;
		void OnDestroy() override;

	private:
		Entity CreateGrass(World* world, const Vector3& position) const;
		Entity CreateDirt(World* world, const Vector3& position) const;
		Entity CreatePlayer(World* world, const Vector3& position);

		void OnKeyPress(FEngine::EKeyCode code);
	private:
		std::unique_ptr<World> m_World = nullptr;

		ListenerHandle m_KeyPressHandle;
	};
}//namespace Fallen