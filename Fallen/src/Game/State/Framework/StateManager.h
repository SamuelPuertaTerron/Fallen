#pragma once

namespace Fallen
{
	enum class EStateType : uint8_t
	{
		Menu,
		Game,
		Pause,
	};

	class IState;

	class StateManager
	{
	public:
		void OnCreate() const;
		void OnTick(float deltaTime) const;
		void OnRender() const;
		void OnDestroy() const; 

		void SetGameState(const std::shared_ptr<IState>& state);

		template<typename T>
		[[nodiscard]] std::shared_ptr<T> GetGameStateAs() const
		{
			static_assert(std::is_base_of_v<IState, T>,
				"T must be derived from IGameState");

			return std::dynamic_pointer_cast<T>(m_CurrentGameState);
		}

	private:
		std::shared_ptr<IState> m_CurrentGameState;
	};
}//namespace Fallen