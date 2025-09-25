#include "FallenGlobals.h"
#include "Fallen.h"

#include "State/Framework/StateFactory.h"
#include "GameData.h"

namespace Fallen
{
	WindowDescription Fallen::GetWindowDescription()
	{
		WindowDescription desc;
		desc.Width = 1270;
		desc.Height = 720;
		desc.Title = "Fallen";
		desc.WindowFlags = EWindowFlags::Resizable;
		desc.UseExitKey = true;
		desc.ExitKeyCode = EKeyCode::F5;
		desc.MaximumFPS = 60;
		return desc;
	}

	void Fallen::OnCreate()
	{
		m_GameStateManager = std::make_unique<StateManager>();
		m_GameStateManager->SetGameState(StateFactory::Create(EStateType::Menu));
	}


	void Fallen::OnTick(float deltaTime)
	{
		m_GameStateManager->OnTick(deltaTime);
	}

	void Fallen::OnRender()
	{
		m_GameStateManager->OnRender();
	}

	void Fallen::OnDestroy()
	{
		m_GameStateManager->OnDestroy();
	}

	void Fallen::OnSystemCreate()
	{
		Render::SetClearColour(Colour::Black());

		Engine::GetInstance().GetEventManager().AddListener<WindowResizeEvent>(EEventType::WindowResize, [&](const WindowResizeEvent& event)
			{
				ResizeWindow(event.Width, event.Height);
			});
	}

	StateManager& Fallen::GetGameStateManager() const
	{
		return *m_GameStateManager;
	}
}//namespace Fallen
