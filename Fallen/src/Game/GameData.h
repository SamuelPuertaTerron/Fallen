#pragma once

namespace Fallen
{
	struct GameData
	{
		Vector3 PlayerPosition = Vector3::Zero();

		//Store all textures here. 
		std::shared_ptr<Texture> GrassTexture = nullptr;
		std::shared_ptr<Texture> DirtTexture = nullptr;
		std::shared_ptr<Texture> HouseTexture = nullptr;
		std::shared_ptr<Texture> PlayerTexture = nullptr;
	};

	static GameData g_GameData = {};
}//namespace