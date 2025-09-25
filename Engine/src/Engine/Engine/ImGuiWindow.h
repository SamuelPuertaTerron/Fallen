#pragma once

namespace FEngine
{
	class Texture;

	struct ImGuiSettings
	{
		bool UseDarkTheme = true;
		bool UseDocking = false;
	};

	class ImGuiWindow
	{
	public:
		ImGuiWindow(const ImGuiSettings& settings);
		~ImGuiWindow();

		void Begin() const;
		void End();

		void BeginWindow(const std::string& title, bool isOpen);
		void EndWindow();

		//Draw Functions
		void DrawText(const std::string& title);
		bool DrawButton(const std::string& title);
		bool DrawTextureButton(const std::shared_ptr<Texture>& texture);
		void DrawTexture(const std::shared_ptr<Texture>& texture);

	private:
		ImGuiSettings m_Settings;
	};
}//namespace FEngine
