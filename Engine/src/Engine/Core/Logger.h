#pragma once

namespace FEngine::Logger
{
	enum class ELogType : uint8_t
	{
		Debug,
		Info,
		Warning,
		Error,
	};

	void Init();

	void Log(ELogType type, const std::string& message);

	void LogCallback(int logLevel, const char* text, va_list args);
}//namespace FEnginez