#include "WorldItGlobals.h"
#include "WorldIt.h"



namespace WorldIt 
{
	WindowDescription WorldIt::GetWindowDescription()
	{
		WindowDescription desc;
		desc.Width = 1270;
		desc.Height = 720;
		desc.Title = "WorldIt";
		desc.WindowFlags = EWindowFlags::Resizable;
		desc.UseExitKey = true;
		desc.ExitKeyCode = EKeyCode::F5;
		desc.MaximumFPS = 60;
		return desc;
	}

	void WorldIt::OnCreate() 
	{
		m_ImGuiWindow = std::make_unique<ImGuiWindow>(ImGuiSettings
			{
				.UseDarkTheme = true,
				.UseDocking = true
			});

		m_TilesetTexture = std::make_shared<Texture>("Resources/Textures/Player.png");
	}

	void WorldIt::OnTick(float deltaTime)
	{
		if (Input::IsKeyDown(EKeyCode::S))
		{
			SaveWorldToJson();
		}

		if (Input::IsKeyDown(EKeyCode::L))
		{
			LoadWorldFromJson();
		}
	}

	void WorldIt::OnRender()
	{
		m_ImGuiWindow->Begin();

		DrawTilesetPanel();
		DrawMainViewport();
		DrawPropertiesPanel();

		m_ImGuiWindow->End();
	}

	void WorldIt::OnDestroy()
	{

	}
	void WorldIt::DrawTilesetPanel()
	{
		m_ImGuiWindow->BeginWindow("Tileset", true);

		m_ImGuiWindow->EndWindow();
	}
	void WorldIt::DrawMainViewport()
	{
		m_ImGuiWindow->BeginWindow("Viewport", true);

		m_ImGuiWindow->EndWindow();
	}
	void WorldIt::DrawPropertiesPanel()
	{
		m_ImGuiWindow->BeginWindow("Properties", true);

		m_ImGuiWindow->EndWindow();
	}
	void WorldIt::SaveWorldToJson()
	{
	}
	void WorldIt::LoadWorldFromJson()
	{
	}
}//namespace WorldIt