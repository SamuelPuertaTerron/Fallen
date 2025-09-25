#include "FallenGlobals.h"
#include "PauseState.h"

#include "Framework/StateFactory.h"
#include "Game/Fallen.h"

namespace Fallen
{
	void PauseState::OnCreate()
	{
		m_KeyPressHandle = Engine::GetInstance().GetEventManager().AddListener<KeyEvent>(
			EEventType::KeyPressed,
			[this](const KeyEvent& e)
			{
				OnKeyPress(e.Key);
			}
		);

		Input::ShouldLockMouseCursor(false);

		Engine::GetInstance().Pause();
	}

	void PauseState::OnTick(float deltaTime)
	{
	}

	void PauseState::OnRender()
	{
		Vector3 position = Window::GetCenter();

		Render::DrawText("Paused", { position.X, position.Y - 250, 0 });

		Render::DrawText("Press Space to Resume", { position.X, position.Y + 50, 0 });

		Render::DrawText("Press Escape to Quit", { position.X, position.Y + 150, 0 });

		m_Initialized = true;
	}

	void PauseState::OnKeyPress(FEngine::EKeyCode code)
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
			Engine::GetInstance().GetGameAs<Fallen>()->GetGameStateManager().SetGameState(StateFactory::Create(EStateType::Menu));
		}
	}
}//namespace Fallen