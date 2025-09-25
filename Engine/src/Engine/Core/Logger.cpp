#include "Globals.h"
#include "Logger.h"

#include "raylib/raylib.h"

namespace FEngine::Logger
{
#ifdef FE_DEBUG
	static bool g_ShouldLogToConsole = true;
#elif FE_RELEASE
	static bool g_ShouldLogToConsole = false;
#endif

	void Init()
	{
		SetTraceLogCallback(LogCallback);
	}

	static void LogToConsole(int logLevel, const std::string& text)
	{
		switch (logLevel)
		{
		case LOG_DEBUG:
			Log(ELogType::Debug, text);
			break;
		case LOG_WARNING:
			Log(ELogType::Warning, text);
			break;
		case LOG_ERROR:
		case LOG_FATAL:
			Log(ELogType::Error, text);
			break;
		default:
			Log(ELogType::Debug, text);
			break;
		}
	}

	static void LogToFile(const std::string& message)
	{
		Path path = "Resources/Log/log.txt";

		if (Filesystem::FileExists(path))
		{
			Filesystem::WriteText(path, message);
		}
	}

	void Log(ELogType type, const std::string& message)
	{
		std::string prefix;
		switch (type)
		{
		case ELogType::Debug:   prefix = "[DEBUG]"; break;
		case ELogType::Warning: prefix = "[WARN]";  break;
		case ELogType::Error:   prefix = "[ERROR]"; break;
		}

		auto output = std::format("{} {}", prefix, message);

		// Send to console
		if (type == ELogType::Error)
		{
			std::cerr << output << '\n';
		}
		else
		{
			std::cout << output << '\n';
		}
	}

	void LogCallback(int logLevel, const char* text, va_list args)
	{
		char buffer[1024];
		vsnprintf(buffer, sizeof(buffer), text, args);
		std::string formatted(buffer);

		if (!g_ShouldLogToConsole)
		{
			LogToFile(formatted);
		}
		else
		{
			LogToConsole(logLevel, formatted);
			LogToFile(formatted);
		}
	}
}//namespace FEngine::Logger