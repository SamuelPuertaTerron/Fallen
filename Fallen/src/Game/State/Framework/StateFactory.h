#pragma once

namespace Fallen
{
	enum class EStateType : uint8_t;

	class IState;

	class StateFactory
	{
	public:
		static std::shared_ptr<IState> Create(EStateType type);
 	};
}//namespace Fallen