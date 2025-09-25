#include "FallenGlobals.h"
#include "StateManager.h"

#include "IState.h"

namespace Fallen
{
	void StateManager::OnCreate() const
	{
		m_CurrentGameState->OnCreate();
	}

	void StateManager::OnTick(float deltaTime) const
	{
		m_CurrentGameState->OnTick(deltaTime);
	}

	void StateManager::OnRender() const
	{
		m_CurrentGameState->OnRender();
	}

	void StateManager::OnDestroy() const
	{
		m_CurrentGameState->OnDestroy();
	}

	void StateManager::SetGameState(const std::shared_ptr<IState>& state)
	{
		if (m_CurrentGameState)
		{
			m_CurrentGameState->OnDestroy();
		}

		m_CurrentGameState = state;
		m_CurrentGameState->OnCreate();
	}
}//namespace Fallen