#pragma once
#include "Framework/IState.h"

namespace Fallen
{
	class PauseState : public IState
	{
	public:
		PauseState() = default;
		~PauseState() override = default;

		void OnCreate() override;
		void OnTick(float deltaTime) override;
		void OnRender() override;
	private:
		void OnKeyPress(FEngine::EKeyCode code);

	private:
		ListenerHandle m_KeyPressHandle;

		bool m_Initialized;
	};
}//namespace Fallen