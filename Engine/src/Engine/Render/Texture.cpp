#include "Globals.h"
#include "Texture.h"

#include <raylib/raylib.h>

namespace FEngine
{
	struct Texture::Impl
	{
		Texture2D Texture = {};
		bool Loaded = false;
	};

	Texture::Texture()
		: m_TextureImpl(std::make_unique<Impl>()) {}

	Texture::Texture(const Path& path)
		: m_TextureImpl(std::make_unique<Impl>())
	{
		if (!Filesystem::FileExists(path))
		{
			Logger::Log(Logger::ELogType::Warning, "The texture path does not exist " + path.string());
			return;
		}

		if (!LoadTextureFromFile(path))
		{
			Logger::Log(Logger::ELogType::Warning, "Failed to load texture at path " + path.string());
			return;
		}
	}

	Texture::~Texture()
	{
		UnLoad();
	}

	bool Texture::LoadTextureFromFile(const Path& path) const
	{
		UnLoad();

		m_TextureImpl->Texture = ::LoadTexture(path.string().c_str());
		m_TextureImpl->Loaded = m_TextureImpl->Texture.id != 0;

		return m_TextureImpl->Loaded;
	}

	int Texture::GetWidth() const
	{
		return m_TextureImpl->Loaded ? m_TextureImpl->Texture.width : 0;
	}

	int Texture::GetHeight() const
	{
		return m_TextureImpl->Loaded ? m_TextureImpl->Texture.height : 0;
	}

	void* Texture::GetRawTexture() const
	{
		return reinterpret_cast<void*>(&m_TextureImpl->Texture);
	}

	void Texture::UnLoad() const
	{
		if (m_TextureImpl->Loaded)
		{
			::UnloadTexture(m_TextureImpl->Texture);
			m_TextureImpl->Loaded = false;
			m_TextureImpl->Texture = {};
		}
	}
}//namespace FEngine