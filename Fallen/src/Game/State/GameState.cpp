#include "FallenGlobals.h"
#include "GameState.h"

#include "Framework/StateFactory.h"
#include "Game/Fallen.h"
#include "Game/GameData.h"

namespace Fallen
{
	GameState::GameState()
	{
		m_World = std::make_unique<World>();
	}

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

		m_World = std::make_unique<World>();

		m_World->GetEntityFactory().RegisterCreator('1', [&](World* world, const Vector3& position) -> Entity 
			{
				return CreateGrass(world, position);
			});

		m_World->GetEntityFactory().RegisterCreator('2', [&](World* world, const Vector3& position) -> Entity 
			{
				return CreateDirt(world, position);
			});

		m_World->GetEntityFactory().RegisterCreator('3', [&](World* world, const Vector3& position) -> Entity 
			{
				return CreatePlayer(world, position);
			});

		m_World->LoadFromFile("Resources/Worlds/World01.fm");

		Engine::GetInstance().Resume();
	}

	void GameState::OnTick(float deltaTime)
	{
		m_World->Tick(deltaTime);
	}

	void GameState::OnRender()
	{
		m_World->Draw();
	}

	void GameState::OnDestroy()
	{
		
	}

	Entity GameState::CreateGrass(World* world, const Vector3& position) const
	{
		static int value = 1;

		Entity entity = { world->GetRegistry().create(), world };
		entity.AddComponent<IdentificationComponent>("Grass" + std::to_string(value), true, Random::Range(10000, 1000000));
		entity.AddComponent<TransformComponent>(position);

		// Assume we have a texture manager
		auto texture = std::make_shared<Texture>("Resources/Textures/Grass.png");
		entity.AddComponent<RenderComponent>(texture, true, RenderComponent::ERenderLayer::Background, Colour::White());

		value++;
		return entity;
	}

	Entity GameState::CreateDirt(World* world, const Vector3& position) const
	{
		static int value = 1;

		Entity entity = { world->GetRegistry().create(), world };
		entity.AddComponent<IdentificationComponent>("Dirt" + std::to_string(value), true, Random::Range(10000, 1000000));
		entity.AddComponent<TransformComponent>(position);

		// Assume we have a texture manager
		auto texture = std::make_shared<Texture>("Resources/Textures/Dirt.png");
		entity.AddComponent<RenderComponent>(texture, true, RenderComponent::ERenderLayer::Background, Colour::White());

		value++;
		return entity;
	}

	Entity GameState::CreatePlayer(World* world, const Vector3& position)
	{
		Entity entity = { world->GetRegistry().create(), world };
		entity.AddComponent<IdentificationComponent>("Player", true, Random::Range(10000, 1000000));
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
		

		// Assume we have a texture manager
		auto texture = std::make_shared<Texture>("Resources/Textures/Player.png");
		entity.AddComponent<RenderComponent>(texture, true, RenderComponent::ERenderLayer::Characters, Colour::White());

		entity.AddComponent<Camera2DComponent>(true, 5.0f, 0.0f);

		ScriptComponent script = {};

		script.OnTick = [](Entity entity, float deltaTime)
			{
				if (Input::IsKeyDown(EKeyCode::W))
				{
					entity.GetTransform().Position.Y -= 10.0f * deltaTime;
				}
				if (Input::IsKeyDown(EKeyCode::S))
				{
					entity.GetTransform().Position.Y += 10.0f * deltaTime;
				}
				if (Input::IsKeyDown(EKeyCode::A))
				{
					entity.GetTransform().Position.X -= 10.0f * deltaTime;
				}
				if (Input::IsKeyDown(EKeyCode::D))
				{
					entity.GetTransform().Position.X += 10.0f * deltaTime;
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