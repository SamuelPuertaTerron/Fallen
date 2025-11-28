#pragma once
#include "Input.h"

namespace FEngine
{
	enum class EWindowFlags : uint16_t
	{
		None = 0,
		Fullscreen = 2,
		Resizable = 4,
		Undecorated = 8,
		Transparent = 16,
		AlwaysRun = 256,
		VSyncHint = 64,

		Default = Fullscreen | VSyncHint | AlwaysRun,
	};

	struct WindowDescription
	{
		int Width = 1270;
		int Height = 720;
		std::string Title;
		int MaximumFPS = 60;

		bool UseExitKey = false;
		EKeyCode ExitKeyCode = EKeyCode::Escape;

		EWindowFlags WindowFlags = EWindowFlags::Default;
	};

	class Window
	{
	public:
		Window(const WindowDescription& description);
		~Window();

		bool IsWindowRunning() const;
		void SetWindowRunning(bool value);

		void ToggleFullscreen() const;

		[[nodiscard]] static Vector3 GetCenter();
		[[nodiscard]] static bool IsWindowResized();

		void WindowResize() const;
	private:
		bool m_bIsWindowRunning;
		WindowDescription m_Description;
	};
}//namespace FEngine