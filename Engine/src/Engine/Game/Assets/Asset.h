#pragma once

#include <any>

#include "Engine/Render/Texture.h"

#include "Engine/Game/World/World.h"

namespace FEngine
{
	class Texture;
	class World;

	enum class EAssetType
	{
		Invalid = 0,

		Texture,
		World,
		Audio,
		Font,
		Script,
	};

	class Asset
	{
	public:
		virtual ~Asset() = default;

		template<typename T>
		std::shared_ptr<T> GetAsset()
		{
			return std::static_pointer_cast<T>(GetRawAsset());
		}

		static std::shared_ptr<Asset> Create(const Path& path, EAssetType type);

	protected:
		virtual std::shared_ptr<void> GetRawAsset() = 0;
	};

	class TextureAsset : public Asset
	{
	public:
		TextureAsset(const Path& path);

		~TextureAsset() override = default;

	protected:
		std::shared_ptr<void> GetRawAsset() override;

	private:
		std::shared_ptr<Texture> m_Texture = nullptr;
	};

	class WorldAsset : public Asset
	{
	public:
		WorldAsset(const Path& path);

		~WorldAsset() override = default;

	protected:
		std::shared_ptr<void> GetRawAsset() override;
	private:
		std::shared_ptr<World> m_World = nullptr;
	};
}//namespace FEngine