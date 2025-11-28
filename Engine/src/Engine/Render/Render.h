#pragma once

#include "Colour.h"

namespace FEngine
{
	enum class EFontAlignment : uint8_t
	{
		Center,
		Right,
		Left,
	};

	struct Camera2DComponent;
	struct TransformComponent;

	class Texture;

	class Render
	{
	public:
		static void BeginRender();
		static void EndRender();

		static Colour GetClearColour();
		static void SetClearColour(Colour colour);

		static void DrawTexture(const std::shared_ptr<Texture>& texture, Vector3 position, Colour colour = Colour::White());

		static void BeginRenderCamera(const Camera2DComponent& camera, const TransformComponent& transform);
		static void EndRenderCamera();

		static void DrawText(const std::string& text, Vector3 position, EFontAlignment alignment = EFontAlignment::Center, float size = 30.0f, Colour colour = Colour::White());
	private:
		inline static Colour m_ClearColour;
	};
}//namespace FEngine