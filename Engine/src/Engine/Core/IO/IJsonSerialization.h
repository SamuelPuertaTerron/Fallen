#pragma once
#include "nlohmann/json_fwd.hpp"

namespace FEngine
{
	using Json = nlohmann::json; //Just to avoid the nlohmann namespace when serializing objects 

	class IJsonSerialization
	{
	public:
		virtual ~IJsonSerialization() = default;

		virtual void SerializeData(Json& out) = 0;
		virtual void DeserializeData(const Json& in) = 0;
	};
}//namespace FEngine