#pragma once

namespace FEngine
{
	struct WindowDescription;
}

namespace FEngine
{
	class IGame
	{
	public:
		virtual ~IGame() = default;

		virtual WindowDescription GetWindowDescription() = 0;
		virtual void OnCreate() = 0;
		virtual void OnTick(float deltaTime) = 0;
		virtual void OnRender() = 0;
		virtual void OnDestroy() = 0;
	};	
}//namespace FEngine