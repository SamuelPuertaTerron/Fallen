#include "Globals.h"
#include "ImGuiWindow.h"

#include "imgui/imgui.h"
#include "rlimgui/rlImGui.h"

#include "Engine/Render/Texture.h"

namespace FEngine
{
	ImGuiWindow::ImGuiWindow(const ImGuiSettings& settings)
	{
		m_Settings = settings;
		rlImGuiSetup(settings.UseDarkTheme);

		if (m_Settings.UseDocking)
		{
			ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		}
	}

	ImGuiWindow::~ImGuiWindow()
	{
		rlImGuiShutdown();
	}

	void ImGuiWindow::Begin() const
	{
		rlImGuiBegin();

		if (m_Settings.UseDocking)
		{
			ImGui::DockSpaceOverViewport(0, nullptr, ImGuiDockNodeFlags_PassthruCentralNode); // set ImGuiDockNodeFlags_PassthruCentralNode so that we can see the raylib contents behind the dockspace
		}
	}

	void ImGuiWindow::End()
	{
		rlImGuiEnd();
	}

	void ImGuiWindow::BeginWindow(const std::string& title, bool isOpen)
	{
		ImGui::Begin(title.c_str(), &isOpen);
	}

	void ImGuiWindow::EndWindow()
	{
		ImGui::End();
	}

	void ImGuiWindow::DrawText(const std::string& title)
	{
		ImGui::Text("%s", title.c_str());
	}

	bool ImGuiWindow::DrawButton(const std::string& title)
	{
		return ImGui::Button(title.c_str());
	}

	bool ImGuiWindow::DrawTextureButton(const std::shared_ptr<Texture>& texture)
	{
		return false;
		//return rlImGuiImageButton("##image_button", texture->GetTexture());
	}

	void ImGuiWindow::DrawTexture(const std::shared_ptr<Texture>& texture)
	{
		//rlImGuiImage(texture->GetTexture());
	}
}//namespace FEngine