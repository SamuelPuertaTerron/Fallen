#pragma once
#include "Asset.h"

namespace FEngine
{
	enum class EAssetType;

	class AssetManager
	{
	public:
		template<typename T>
		static std::shared_ptr<T> GetAsset(const Path& path)
		{
			if (m_Assets.contains(path))
			{
				return std::static_pointer_cast<T>(m_Assets[path]->GetAsset<T>());
			}

			return nullptr;
		}

		template<typename T>
		static std::shared_ptr<T> LoadAsset(const Path& path, EAssetType type)
		{
			if (m_Assets.contains(path))
			{
				return std::static_pointer_cast<T>(m_Assets[path]->GetAsset<T>());
			}

			auto asset = Asset::Create(path, type);
			m_Assets[path] = asset;
			return std::static_pointer_cast<T>(asset);
		}

		static void CreateAsset(const Path& path, EAssetType type);
	private:
		static inline std::unordered_map<Path, std::shared_ptr<Asset>> m_Assets;
	};
}//namespace FEngine