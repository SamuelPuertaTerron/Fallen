#include "Globals.h"
#include "Engine.h"

#include <raylib/raylib.h>

#include "EventManager.h"
#include "IGame.h"
#include "Window.h"
#include "Engine/Render/Render.h"

namespace FEngine
{
	Engine& Engine::GetInstance()
	{
		if (!m_pEngineInstance)
		{
			m_pEngineInstance = new Engine();
		}

		return *m_pEngineInstance;
	}

	Engine::~Engine()
	{
		delete m_pEngineInstance;
	}

	void Engine::CalculateDeltaTime()
	{
		m_CurrentTime = static_cast<float>(GetTime());
		m_UnscaledDeltaTime = m_CurrentTime - m_PreviousTime;
		m_DeltaTime = m_UnscaledDeltaTime * m_TimeScale;
		m_PreviousTime = m_CurrentTime;
	}

	void Engine::CreateAndRun(const std::shared_ptr<IGame>& game)
	{
		Logger::Init();

		m_Game = game;

		m_Window = std::make_unique<Window>(m_Game->GetWindowDescription());
		m_EventManager = std::make_unique<EventManager>();

		m_Game->OnCreate();

		m_PreviousTime = static_cast<float>(GetTime());

		while (m_Window->IsWindowRunning())
		{
			CalculateDeltaTime();

			m_EventManager->PollEvents();

			m_Game->OnTick(m_DeltaTime);

			Render::BeginRender();

			m_Game->OnRender();

			Render::EndRender();
		}

		m_Game->OnDestroy();
	}

	void Engine::Quit() const
	{
		m_Window->SetWindowRunning(false);
	}
}//namespace FEngine