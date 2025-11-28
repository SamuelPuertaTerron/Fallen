#include "Globals.h"
#include "Asset.h"

#include "Engine/Render/Texture.h"

namespace FEngine
{
    std::shared_ptr<Asset> Asset::Create(const Path& path, EAssetType type)
    {
	    switch (type)
	    {
	    case EAssetType::Texture:
			Logger::Log(Logger::ELogType::Info, std::format("Created Texture Asset at path {}", path.string()));
			return std::make_shared<TextureAsset>(path);
	    case EAssetType::World:
			Logger::Log(Logger::ELogType::Info, std::format("Created World Asset at path {}", path.string()));
			return std::make_shared<WorldAsset>(path);
	    }

		return nullptr;
    }

	WorldAsset::WorldAsset(const Path& path)
	{
		m_World = std::make_shared<World>();
	}

	std::shared_ptr<void> WorldAsset::GetRawAsset()
	{
		return m_World;
	}

	TextureAsset::TextureAsset(const Path& path)
	{
		m_Texture = std::make_shared<Texture>(path);
	}

	std::shared_ptr<void> TextureAsset::GetRawAsset()
	{
		return m_Texture;
	}
}//namespace FEngine