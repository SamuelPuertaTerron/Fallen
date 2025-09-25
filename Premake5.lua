workspace("Fallen")
    configurations {"Debug", "ReleaseDebug", "Release"}
    architecture("x64")
    startproject "Fallen"

    flags {"MultiProcessorCompile"}

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    cwd = _MAIN_SCRIPT_DIR

    IncludeDir = {}
    IncludeDir["Engine"] = cwd .. "/Engine/src"
    IncludeDir["RaylibDir"] = cwd .. "/ThirdParty/raylib/include"
    IncludeDir["Entt"] = cwd .. "/ThirdParty/entt"
    IncludeDir["Box2D"] = cwd .. "/ThirdParty/box2d/include"
    IncludeDir["ImGuiBase"] = cwd .. "/ThirdParty/imguibase"
    IncludeDir["Nlohmannjson"] = cwd .. "/ThirdParty/nlohmannjson/include"

    filter "Debug"
    symbols "on"

    filter "Release"
    optimize "on"
    symbols "off"

    group "Engine"
        include "Engine"
        include "WorldIt"
    group ""

    group "Games"
        include "Fallen"
    group ""

    group "ThirdParty"
        include "ThirdParty/Box2d"
        include "ThirdParty/Entt"
        include "ThirdParty/ImGuiBase"
        include "ThirdParty/raylib"
        include "ThirdParty/nlohmannjson"
    group ""
