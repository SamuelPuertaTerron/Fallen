#include "Globals.h"
#include "Input.h"

#include <raylib/raylib.h>

namespace FEngine
{
	bool Input::IsKeyPressed(EKeyCode keyCode)
	{
		return ::IsKeyPressed(static_cast<int>(keyCode));
	}

	bool Input::IsKeyDown(EKeyCode keyCode)
	{
		return ::IsKeyDown(static_cast<int>(keyCode));
	}

	bool Input::IsMouseButtonPressed(EMouseButton button)
	{
		return ::IsMouseButtonPressed(static_cast<int>(button));
	}

	bool Input::IsMouseButtonDown(EMouseButton button)
	{
		return ::IsMouseButtonDown(static_cast<int>(button));
	}
	void Input::ShouldShowMouseCursor(bool value)
	{
		if (value)
		{
			::ShowCursor();
		}
		else
		{
			::HideCursor();
		}
	}
	void Input::ShouldLockMouseCursor(bool value)
	{
		if (value)
		{
			::DisableCursor();
		}
		else
		{
			::EnableCursor();
		}
	}
}//namespace FEngine