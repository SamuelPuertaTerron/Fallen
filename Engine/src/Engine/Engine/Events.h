#pragma once
#include "Input.h"

namespace FEngine
{
	enum class EEventType : uint32_t
	{
		Unknown = 0,

		//Window
		WindowResize,

		// Input
		KeyPressed,
		KeyReleased,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled,
	};

	struct Event
	{
		EEventType Type = EEventType::Unknown;
		virtual ~Event() = default;
	};

	struct WindowResizeEvent : Event
	{
		int Width;
		int Height;
		WindowResizeEvent(int w, int h)
		{
			Type = EEventType::WindowResize;
			Width = w; Height = h;
		}
	};

	struct KeyEvent : Event
	{
		EKeyCode Key;
		KeyEvent(EEventType type, EKeyCode key)
		{
			Type = type;
			Key = key;
		}
	};

	struct MouseButtonEvent : Event
	{
		EMouseButton Button;
		MouseButtonEvent(EEventType type, EMouseButton button)
		{
			Type = type;
			Button = button;
		}
	};

	struct MouseMoveEvent : Event
	{
		float X;
		float Y;
		MouseMoveEvent(float x, float y)
		{
			Type = EEventType::MouseMoved;
			X = x; Y = y;
		}
	};

	struct MouseScrollEvent : Event
	{
		float OffsetX;
		float OffsetY;
		MouseScrollEvent(float x, float y)
		{
			Type = EEventType::MouseScrolled;
			OffsetX = x; OffsetY = y;
		}
	};
}//namespace FEngine