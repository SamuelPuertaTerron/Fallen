#pragma once

namespace FEngine
{
	class Time
	{
	public:

		static void Init();

		static void SetTimeScale(float scale);
		static float GetTimeScale();
		static void Pause();
		static void Resume();
		 
		static float GetDeltaTime();
		static float GetUnscaledDeltaTime();

		//Note: Internal Function used inside the Engine class
		static void CalculateDeltaTime();

	private:
		static inline float s_UnscaledDeltaTime;  // Raw delta time
		static inline float s_DeltaTime; //Scaled delta time used inside the tick functions. 
		static inline float s_CurrentTime;
		static inline float s_PreviousTime;
		static inline float s_TimeScale;
	};

}//namespace FEngine