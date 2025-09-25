project "Fallen"
	language "C++"
	cppdialect "C++20"
    kind "ConsoleApp"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "FallenGlobals.h"
    pchsource "src/FallenGlobals.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{		
        "src",
        "%{IncludeDir.Engine}",
		"%{IncludeDir.RaylibDir}",
		"%{IncludeDir.Box2d}",
		"%{IncludeDir.Entt}",
	}

	links
	{
        "Engine",
	}

    linkoptions { "/IGNORE:4006" } -- For winmm library

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"FE_PLATFORM_WINDOWS",
			"_CRT_SECURE_NO_WARNINGS"
		}

		postbuildcommands 
		{
			"{COPYDIR} Resources %{cfg.targetdir}/Resources"
		}

	filter "configurations:Debug"
        defines
        {
            "FE_DEBUG"
        }
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
        defines
        {
            "FE_RELEASE"
        }
		kind "WindowedApp"
		runtime "Release"
        optimize "on"
		symbols	 "off"