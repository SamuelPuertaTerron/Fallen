#include "Globals.h"
#include "AssetManager.h"

#include "Asset.h"

namespace FEngine
{
	void AssetManager::CreateAsset(const Path& path, EAssetType type)
	{
		m_Assets[path] = Asset::Create(path, type);
	}
}//namespace FEngine