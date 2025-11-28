#include "Globals.h"
#include "Time.h"

#include "raylib/raylib.h"

namespace FEngine
{
	void Time::Init()
	{
		s_PreviousTime = static_cast<float>(::GetTime());
	}

	void Time::SetTimeScale(float scale)
	{
		s_TimeScale = scale;
	}

	float Time::GetTimeScale()
	{
		return s_TimeScale;
	}

	void Time::Pause()
	{
		SetTimeScale(0.0f);
	}

	void Time::Resume()
	{
		SetTimeScale(1.0f);
	}

	float Time::GetDeltaTime()
	{
		return s_DeltaTime;
	}

	float Time::GetUnscaledDeltaTime()
	{
		return s_UnscaledDeltaTime;
	}

	void Time::CalculateDeltaTime()
	{
		s_CurrentTime = static_cast<float>(::GetTime());
		s_UnscaledDeltaTime = s_CurrentTime - s_PreviousTime;
		s_DeltaTime = s_UnscaledDeltaTime * s_TimeScale;
		s_PreviousTime = s_CurrentTime;
	}
}//namespace FEngine