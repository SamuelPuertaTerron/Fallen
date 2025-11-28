#pragma once

namespace FEngine
{
	class IJsonSerialization;

	class JsonSerializer
	{
	public:
		static void SerializeObject(const Path& path, IJsonSerialization& object);
		static void DeserializeObject(const Path& path, IJsonSerialization& object);
	};
}//namespace FEngine 
