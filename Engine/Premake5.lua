project "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "Globals.h"
    pchsource "src/Globals.cpp"

    files 
	{
        "src/**.h",
        "src/**.cpp"
    }

    includedirs 
	{
        "%{IncludeDir.RaylibDir}",
        "%{IncludeDir.Engine}",
        "%{IncludeDir.Entt}",
        "%{IncludeDir.Box2d}",
        "%{IncludeDir.ImGuiBase}",
        "%{IncludeDir.Nlohmannjson}"
    }

    links 
	{
        "raylib",
        "Box2d",
        "Entt",
        "ImGuiBase",
        "nlohmann"
    }

    linkoptions { "/IGNORE:4006" } -- For winmm library

    filter "system:windows"
        systemversion "latest"
        defines 
        {
            "FE_PLATFORM_WINDOWS",
            "_CRT_SECURE_NO_WARNINGS"
        }

        links 
        {
            "opengl32",
            "gdi32",
            "winmm"
        }

    filter "configurations:Debug"
        defines { "FE_DEBUG" }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines { "FE_RELEASE" }
        runtime "Release"
        symbols "off"
        optimize "on"
