#include "FallenGlobals.h"
#include "MenuState.h"

#include "Framework/StateFactory.h"
#include "Game/Fallen.h"

namespace Fallen
{
	void MenuState::OnCreate()
	{
		m_KeyPressHandle = Engine::GetInstance().GetEventManager().AddListener<KeyEvent>(
			EEventType::KeyPressed,
			[this](const KeyEvent& e)
			{
				OnKeyPress(e.Key);
			}
		);

		Input::ShouldLockMouseCursor(false);
	}

	void MenuState::OnTick(float deltaTime)
	{
	}


	void MenuState::OnRender()
	{
		Vector3 position = Window::GetCenter();

		Render::DrawText("Fallen", { position .X, position.Y - 250, 0});

		Render::DrawText("Press Space to Play", { position.X, position.Y + 50, 0 });

		Render::DrawText("Press Escape to Quit", { position.X, position.Y + 150, 0 });

		m_Initialized = true;
	}

	void MenuState::OnKeyPress(FEngine::EKeyCode code)
	{
		if (!m_Initialized)
		{
			return;
		}

		if (code == EKeyCode::Space)
		{
			Engine::GetInstance().GetGameAs<Fallen>()->GetGameStateManager().SetGameState(StateFactory::Create(EStateType::Game));
		}

		if (code == EKeyCode::Escape)
		{
			Engine::GetInstance().Quit();
		}
	}
}//namespace Fallen