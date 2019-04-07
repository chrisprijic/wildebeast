workspace "Wildebeast"
    architecture "x64"
    startproject "Game"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include dirs relative to root (solution)
IncludeDir = {}

project "Wildebeast"
    location "Wildebeast"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/{prj.name}")

   -- pchheader "wbpch.h"
    --pchsource "Wildebeast/src/wbpch.cpp"

    files 
    {
        "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
    }

    links
    {

    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "WB_PLATFORM_WINDOWS",
            "WB_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Game/\"")
        }

    filter "configurations:Debug"
        defines "WB_DEBUG"
        runtime "DEBUG"
        symbols "on"

    filter "configurations:Release"
		defines "WB_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "WB_DIST"
		runtime "Release"
        optimize "on"
        
project "Game"
    location "Game"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Wildebeast/src",
        "Wildebeast/vendor"
    }

    links
    {
        "Wildebeast"
    }

    filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"WB_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "WB_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "WB_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "WB_DIST"
		runtime "Release"
		optimize "On"
