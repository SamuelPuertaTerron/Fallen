#include "Globals.h"
#include "Render.h"

#include "raylib/raylib.h"

#include "Engine/Engine/Window.h"
#include "Engine/Game/World/Components.h"

#include "Texture.h"

namespace FEngine
{
	static constexpr ::Color ConvertToRaylibColour(Colour colour)
	{
		return
		{
			static_cast<unsigned char>(colour.R * 255),
			static_cast<unsigned char>(colour.G * 255),
			static_cast<unsigned char>(colour.B * 255),
			static_cast<unsigned char>(colour.A * 255),
		};
	}

	static ::Camera2D ToRaylibCamera(const Camera2DComponent& cam, const TransformComponent& transform)
	{
		::Vector2 windowCenter = { Window::GetCenter().X, Window::GetCenter().Y };

		::Camera2D rlCam;
		rlCam.target = { transform.Position.X, transform.Position.Y };
		rlCam.offset = windowCenter;
		rlCam.rotation = cam.Rotation;
		rlCam.zoom = cam.Size;
		return rlCam;
	}

	void Render::BeginRender()
	{
		::BeginDrawing();
		::ClearBackground(ConvertToRaylibColour(m_ClearColour));
	}

	void Render::EndRender()
	{
		::EndDrawing();
	}

	Colour Render::GetClearColour()
	{
		return m_ClearColour;
	}

	void Render::SetClearColour(Colour colour)
	{
		m_ClearColour = colour;
	}

	void Render::DrawTexture(const std::shared_ptr<Texture>& texture, Vector3 position, Colour colour)
	{
		::Texture tex = texture->GetTexture();
		::DrawTextureV(tex, { position.X, position.Y }, ConvertToRaylibColour(colour));
	}

	void Render::BeginRenderCamera(const Camera2DComponent& camera, const TransformComponent& transform)
	{
		const ::Camera2D raylibCamera = ToRaylibCamera(camera, transform);
		BeginMode2D(raylibCamera);
	}

	void Render::EndRenderCamera()
	{
		::EndMode2D();
	}

	void Render::DrawText(const std::string& text, Vector3 position, EFontAlignment alignment, float size, Colour colour)
	{
		::Font font = ::GetFontDefault();
		::Vector2 textSize = MeasureTextEx(font, text.c_str(), size, 5);

		Vector3 drawPos = position;

		switch (alignment)
		{
		case EFontAlignment::Center:
			drawPos.X -= textSize.x / 2.0f;
			drawPos.Y -= textSize.y / 2.0f;
			break;
		case EFontAlignment::Right:
			drawPos.X -= textSize.x;
			break;
		case EFontAlignment::Left:
			break;
		}

		::DrawTextEx(font, text.c_str(), {drawPos.X, drawPos.Y}, size, 5, ConvertToRaylibColour(colour));
	}
}//namespace FEngine