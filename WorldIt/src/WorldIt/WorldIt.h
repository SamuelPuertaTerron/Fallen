#pragma once

namespace WorldIt 
{
	class WorldIt : public IGame
	{
    public:
        WorldIt()
            : m_TileGrid(20, std::vector<int>(15, 0)) {}
        ~WorldIt() override = default;

        WindowDescription GetWindowDescription() override;
        void OnCreate() override;
        void OnTick(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

    private:
        void DrawTilesetPanel();
        void DrawMainViewport();
        void DrawPropertiesPanel();
        void SaveWorldToJson();
        void LoadWorldFromJson();

        std::unique_ptr<ImGuiWindow> m_ImGuiWindow;
        std::shared_ptr<Texture> m_TilesetTexture;

        std::vector<std::vector<int>> m_TileGrid;
        Vector3 m_GridSize = { 20, 15, 0 };
        float m_TileSize = 32.0f;

        int m_SelectedTile = 0;
        Vector3 m_TilesetGridSize = { 8, 8,0 };
        Vector3 m_ViewportScroll = { 0, 0, 0 };

        std::string m_CurrentFile = "world.json";
	};
}//namespace WorldIt
