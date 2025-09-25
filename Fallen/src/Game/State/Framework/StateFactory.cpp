#include "FallenGlobals.h"
#include "StateFactory.h"

#include "StateManager.h"

#include "Game/State/GameState.h"
#include "Game/State/MenuState.h"
#include "Game/State/PauseState.h"

namespace Fallen
{
	std::shared_ptr<IState> StateFactory::Create(EStateType type)
	{
		switch (type)
		{
		case EStateType::Menu:
			return std::make_shared<MenuState>();
		case EStateType::Game:
			return std::make_shared<GameState>();
		case EStateType::Pause:
			return std::make_shared<PauseState>();
		default:
			return nullptr;
		};
	}
}//namespace Fallen