#include "Globals.h"
#include "Texture.h"

namespace FEngine
{
	Texture::Texture(const Path& path)
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

	bool Texture::LoadTextureFromFile(const Path& path)
	{
		UnLoad();

		m_Texture = ::LoadTexture(path.string().c_str());
		m_IsLoaded = m_Texture.id != 0;

		return m_IsLoaded;
	}

	int Texture::GetWidth() const
	{
		return m_IsLoaded ? m_Texture.width : 0;
	}

	int Texture::GetHeight() const
	{
		return m_IsLoaded ? m_Texture.height : 0;
	}

	::Texture Texture::GetTexture() const
	{
		return m_Texture;
	}

	void Texture::UnLoad() const
	{
		if (m_IsLoaded)
		{
			::UnloadTexture(m_Texture);
		}
	}
}//namespace FEngine