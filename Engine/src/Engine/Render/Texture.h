#pragma once
#include "raylib/raylib.h"

namespace FEngine
{
	class Texture
	{
	public:
		Texture(const Path& path);
		~Texture();

		bool LoadTextureFromFile(const Path& path);

		int GetWidth() const;
		int GetHeight() const;

		::Texture GetTexture() const;

		void UnLoad() const;

		// No copy
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

	private:
		::Texture m_Texture;
		bool m_IsLoaded;
	};
}//namespace FEngine
