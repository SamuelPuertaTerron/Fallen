#pragma once
#include <functional>
#include <memory>
#include <iterator>

#include <filesystem>
#include <fstream>

#include <iostream>

#include <map>
#include <string>

#include "Engine/Engine/Engine.h"

#include "Engine/Core/Random.h"
#include "Engine/Core/Filesystem.h"
#include "Engine/Core/Vector3.h"

#include "Engine/Core/Logger.h"

namespace FEngine::Assert
{
	static void Assert(bool condition, const char* file, int line, const char* message)
	{
		if (!condition)
		{
			std::string formatted = std::format("Condition {} in file {} at line {}. Message: {}", condition, file, line, message);
			Logger::Log(Logger::ELogType::Error, formatted);
			std::abort();
		}
	}
}//namespace FEngine::Assert

#define ASSERT(cond, msg) FEngine::Assert::Assert((cond), __FILE__, __LINE__, msg)

namespace FEngine
{

}//namespace FEngine