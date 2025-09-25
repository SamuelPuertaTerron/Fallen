#pragma once

namespace Fallen
{
	class IState
	{
	public:
		virtual ~IState() = default;

		virtual void OnCreate() {}
		virtual void OnTick(float deltaTime) = 0;
		virtual void OnRender() = 0;
		virtual void OnDestroy() {}
	};
}//namespace Fallen