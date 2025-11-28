#pragma once

namespace Fallen
{
	struct GameData
	{
		Vector3 PlayerPosition = Vector3::Zero();
	};

	static GameData g_GameData = {};
}//namespace