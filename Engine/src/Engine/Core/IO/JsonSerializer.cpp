#include "Globals.h"
#include "JsonSerializer.h"

#include "nlohmann/json.hpp"

#include "Engine/Core/IO/IJsonSerialization.h"

namespace FEngine
{
	void JsonSerializer::SerializeObject(const Path& path, IJsonSerialization& object)
	{
		nlohmann::json json;

		object.SerializeData(json);

		std::stringstream fileText;
		fileText << json;

		if (!Filesystem::FileExists(path))
		{
			Filesystem::CreateFile(path);
		}

		Filesystem::WriteText(path, fileText.str(), EFileWriteMode::Replace);
	}

	void JsonSerializer::DeserializeObject(const Path& path, IJsonSerialization& object)
	{
		std::ifstream file(path);
		nlohmann::json json;
		file >> json;

		object.DeserializeData(json);
	}
}//namespace FEngine