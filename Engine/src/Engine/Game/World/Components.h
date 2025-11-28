#pragma once
#include "Engine/Render/Colour.h"

namespace FEngine
{
	class Entity;

	struct IdentificationComponent
	{
		std::string Name;
		bool IsActive = true;
		uint32_t ID = -1;

		IdentificationComponent(const std::string& name, bool isActive, uint32_t id)
			: Name(name), IsActive(isActive), ID(id) {}

		IdentificationComponent() = default;
	};

	struct TransformComponent
	{
		Vector3 Position;
		Vector3 Rotation;
		Vector3 Scale;

		TransformComponent() : Position{ 0 }, Rotation{ 0 }, Scale{ 1 } {}
		TransformComponent(Vector3 position) : Position(position), Rotation{ 0, }, Scale{ 1, } {}
	};

	struct RenderComponent
	{
		enum class ERenderLayer : uint8_t
		{
			Default = 0,
			Background = 1,
			Props = 2,
			Dynamic = 3,
			Characters = 4,
			Foreground = 5,
		};

		std::shared_ptr<Texture> Texture;
		bool IsVisible;
		ERenderLayer RenderLayer;
		int ZOrder = 0;
		Colour Colour;

		RenderComponent() = default;

		RenderComponent(const std::shared_ptr<class Texture>& texture, bool visible, ERenderLayer renderLayer, struct Colour colour)
			: Texture(texture), IsVisible(visible), RenderLayer(renderLayer), Colour(colour) {}
	};

	struct Camera2DComponent
	{
		bool IsMainCamera;
		float Size;
		float Rotation;

		Camera2DComponent()
			: IsMainCamera(true), Size(10), Rotation(0) {}

		Camera2DComponent(bool isMainCamera, float size, float rotation)
			:IsMainCamera(isMainCamera), Size(size), Rotation(rotation) {}
	};

	struct ScriptComponent
	{
		using TickFunc = std::function<void(Entity, float)>;
		using GenericFunc = std::function<void(Entity)>;

		GenericFunc OnCreate  = nullptr; //Called when the object is created or when the object is reactived
		TickFunc    OnTick    = nullptr; //Called every frame when the object is active
		GenericFunc OnDestroy = nullptr; //Called when the object is destroyed or when the object is deactived;
	};
}//namespace FEngine