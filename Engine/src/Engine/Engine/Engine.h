#pragma once
#include "IGame.h"

namespace FEngine
{
	class Window;
	class IGame;
	class EventManager;

	class Engine
	{
	public:
		static Engine& GetInstance();

		void CreateAndRun(const std::shared_ptr<IGame>& game);

		void Quit() const;

		Window& GetWindow() const { return *m_Window; }
		EventManager& GetEventManager() const { return *m_EventManager; }

		template<typename T>
		requires std::derived_from<T, IGame>
		[[nodiscard]] std::shared_ptr<T> GetGameAs() const
		{
			return std::dynamic_pointer_cast<T>(m_Game);
		}

	private:
		Engine() = default;
		~Engine();
	private:
		inline static Engine* m_pEngineInstance = nullptr;

		std::shared_ptr<IGame> m_Game;
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<EventManager> m_EventManager;
	};
}//namespace FEngine