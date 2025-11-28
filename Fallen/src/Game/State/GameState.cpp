#include "FallenGlobals.h"
#include "GameState.h"

#include "Framework/StateFactory.h"
#include "Game/Fallen.h"
#include "Game/GameData.h"
#include "Game/Serialization/GameSerialization.h"

namespace Fallen
{
	void GameState::OnCreate()
	{
		m_KeyPressHandle = Engine::GetInstance().GetEventManager().AddListener<KeyEvent>(
			EEventType::KeyPressed,
			[this](const KeyEvent& e)
			{
				OnKeyPress(e.Key);
			}
		);

		Input::ShouldLockMouseCursor(true);

		m_World = AssetManager::GetAsset<World>("Resources/Worlds/World01.fm");

		CreatePlayer(m_World.get(), { 0.0f, 0.0f, 0.0f });

		for (size_t x = 0; x <= 10; x++)
		{
			for (size_t y = 0; y <= 10; y++)
			{
				CreateGrass(m_World.get(), { 32 * static_cast<float>(x), 32 * static_cast<float>(y), 0.0f });
			}
		}

		m_GameSerialization = new GameSerialization{ m_World.get() };

		Time::Resume();
	}

	void GameState::OnTick(float deltaTime)
	{
		m_World->Tick(deltaTime);

		if (Input::IsKeyPressed(EKeyCode::O))
		{
			//JsonSerializer::SerializeObject("Resources/Data/GameData.json", *m_GameSerialization);
			m_World->SaveWorld("Resources/Worlds/World.fworld");
		}

		if (Input::IsKeyPressed(EKeyCode::L))
		{
			JsonSerializer::DeserializeObject("Resources/Data/GameData.json", *m_GameSerialization);
		}
	}

	void GameState::OnRender()
	{
		m_World->Draw();
	}

	void GameState::OnDestroy()
	{
		delete m_GameSerialization;
	}

	Entity GameState::CreateGrass(World* world, const Vector3& position) const
	{
		static int value = 1;

		Entity entity = world->CreateEntity("Grass" + std::to_string(value));
		entity.AddComponent<TransformComponent>(position);

		auto texture = AssetManager::GetAsset<Texture>("Resources/Textures/Grass.png");
		entity.AddComponent<RenderComponent>(texture, true, RenderComponent::ERenderLayer::Background, Colour::White());

		value++;
		return entity;
	}

	Entity GameState::CreateDirt(World* world, const Vector3& position) const
	{
		static int value = 1;

		Entity entity = world->CreateEntity("Dirt" + std::to_string(value));
		entity.AddComponent<TransformComponent>(position);

		auto texture = AssetManager::GetAsset<Texture>("Resources/Textures/Dirt.png");
		entity.AddComponent<RenderComponent>(texture, true, RenderComponent::ERenderLayer::Background, Colour::White());

		value++;
		return entity;
	}

	Entity GameState::CreatePlayer(World* world, const Vector3& position)
	{
		Entity entity = world->CreateEntity("Player");
		entity.AddComponent<TransformComponent>(position);

		if (g_GameData.PlayerPosition == Vector3::Zero())
		{
			entity.GetComponent<TransformComponent>().Position.X = 100.0f;
			entity.GetComponent<TransformComponent>().Position.Y = 100.0f;
		}
		else
		{
			entity.GetComponent<TransformComponent>().Position = g_GameData.PlayerPosition;
		}
		

		auto texture = AssetManager::GetAsset<Texture>("Resources/Textures/Player.png");
		entity.AddComponent<RenderComponent>(texture, true, RenderComponent::ERenderLayer::Characters, Colour::White());

		entity.AddComponent<Camera2DComponent>(true, 5.0f, 0.0f);

		ScriptComponent script = {};

		script.OnTick = [](Entity entity, float deltaTime)
			{
				if (Input::IsKeyDown(EKeyCode::W))
				{
					entity.GetTransform().Position.Y -= 25.0f * deltaTime;
				}
				if (Input::IsKeyDown(EKeyCode::S))
				{
					entity.GetTransform().Position.Y += 25.0f * deltaTime;
				}
				if (Input::IsKeyDown(EKeyCode::A))
				{
					entity.GetTransform().Position.X -= 25.0f * deltaTime;
				}
				if (Input::IsKeyDown(EKeyCode::D))
				{
					entity.GetTransform().Position.X += 25.0f * deltaTime;
				}

				g_GameData.PlayerPosition = entity.GetTransform().Position;
			};

		entity.AddComponent<ScriptComponent>(script);

		return entity;
	}
	void GameState::OnKeyPress(FEngine::EKeyCode code)
	{
		if (code == EKeyCode::Escape)
		{
			Engine::GetInstance().GetGameAs<Fallen>()->GetGameStateManager().SetGameState(StateFactory::Create(EStateType::Pause));
		}
	}
}//namespace Fallen