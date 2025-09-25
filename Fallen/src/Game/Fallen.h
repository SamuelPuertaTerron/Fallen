#pragma once

#include "State/Framework/StateManager.h"

namespace Fallen
{
	class Fallen : public IGame
	{
	public:
		Fallen() = default;
		~Fallen() override = default;

		WindowDescription GetWindowDescription() override;

		void OnCreate() override;

		void OnTick(float deltaTime) override;

		void OnRender() override;

		void OnDestroy() override;

		void OnSystemCreate();

		void ResizeWindow(int width, int height)
		{
			m_Width = width;
			m_Height = height;
		}

		[[nodiscard]] StateManager& GetGameStateManager() const;

	private:
		std::unique_ptr<StateManager> m_GameStateManager = nullptr;

		int m_Width, m_Height;
	};

}//namespace Fallen
