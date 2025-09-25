#include "Globals.h"
#include "Window.h"

#include "EventManager.h"
#include "raylib/raylib.h"


namespace FEngine
{
	static constexpr unsigned int ToRaylibFlags(EWindowFlags flags)
	{
		return static_cast<unsigned int>(flags);
	}

	static constexpr bool HasFlag(EWindowFlags value, EWindowFlags flag)
	{
		using windowFlags = std::underlying_type_t<EWindowFlags>;
		return (static_cast<windowFlags>(value) & static_cast<windowFlags>(flag)) != 0;
	}

	Window::Window(const WindowDescription& description)
	{
		m_Description = description;

		int width = description.Width;
		int height = description.Height;

		if (HasFlag(description.WindowFlags, EWindowFlags::Fullscreen))
		{
			int monitor = GetCurrentMonitor();
			width = GetMonitorWidth(monitor);
			height = GetMonitorHeight(monitor);
		}

		SetConfigFlags(ToRaylibFlags(description.WindowFlags));

		InitWindow(width, height, description.Title.c_str());
		

		int useEscapeKey = description.UseExitKey ? static_cast<int>(description.ExitKeyCode) : static_cast<int>(KEY_NULL);
		SetExitKey(useEscapeKey);

		m_bIsWindowRunning = true;
	}

	Window::~Window()
	{
		CloseWindow();
	}

	bool Window::IsWindowRunning() const
	{
		return m_bIsWindowRunning && !WindowShouldClose();
	}

	void Window::SetWindowRunning(bool value)
	{
		m_bIsWindowRunning = value;
	}

	void Window::ToggleFullscreen() const
	{
		int display = GetCurrentMonitor();

		if (IsWindowFullscreen())
		{
			SetWindowSize(m_Description.Width, m_Description.Height);
		}
		else
		{
			SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
		}

		::ToggleFullscreen();
	}

	Vector3 Window::GetCenter()
	{
		float width = static_cast<float>(GetScreenWidth()) / 2;
		float height = static_cast<float>(GetScreenHeight()) / 2;

		return { width, height, 0.0f };
	}

	bool Window::IsWindowResized()
	{
		return ::IsWindowResized();
	}

	void Window::WindowResize() const
	{
		if (!IsWindowResized())
		{
			return;
		}

		int width = GetScreenWidth();
		int height = GetScreenHeight();

		Engine::GetInstance().GetEventManager().PushEvent<WindowResizeEvent>(width, height);
	}
}//namespace FEngine