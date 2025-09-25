#pragma once
#include "Framework/IState.h"

namespace Fallen
{
	class MenuState : public IState
	{
	public:
		MenuState()
			: m_KeyPressHandle(), m_Initialized(false) {}

		~MenuState() override = default;

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
