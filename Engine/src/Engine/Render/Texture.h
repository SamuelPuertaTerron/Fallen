#pragma once
namespace FEngine
{
	class Texture
	{
	public:
		Texture();
		Texture(const Path& path);
		~Texture();

		bool LoadTextureFromFile(const Path& path) const;

		int GetWidth() const;
		int GetHeight() const;

		template<typename T>
		T* GetTextureAs() const
		{
			return static_cast<T*>(GetRawTexture());
		}

		void* GetRawTexture() const;

		void UnLoad() const;

		// No copy
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

	private:
		struct Impl;
		std::unique_ptr<Impl> m_TextureImpl;
	};
}//namespace FEngine
