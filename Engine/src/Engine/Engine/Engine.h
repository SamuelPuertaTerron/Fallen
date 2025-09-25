#pragma once

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

		// Time scaling methods
		void SetTimeScale(float scale) { m_TimeScale = scale; }
		float GetTimeScale() const { return m_TimeScale; }
		void Pause() { SetTimeScale(0.0f); }
		void Resume() { SetTimeScale(1.0f); }

		// Delta time accessors
		float GetDeltaTime() const { return m_DeltaTime; }
		float GetUnscaledDeltaTime() const { return m_UnscaledDeltaTime; }

		template<typename T>
		[[nodiscard]] std::shared_ptr<T> GetGameAs() const
		{
			static_assert(std::is_base_of_v<IGame, T>,
				"T must be derived from IGameState");

			return std::dynamic_pointer_cast<T>(m_Game);
		}

	private:
		Engine() = default;
		~Engine();

		void CalculateDeltaTime();
	private:

		inline static Engine* m_pEngineInstance = nullptr;

		std::shared_ptr<IGame> m_Game;
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<EventManager> m_EventManager;

		float m_UnscaledDeltaTime;  // Raw delta time
		float m_DeltaTime; //Scaled delta time used inside the tick functions. 
		float m_CurrentTime;
		float m_PreviousTime;
		float m_TimeScale;
	};
}//namespace FEngine