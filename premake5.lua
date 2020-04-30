workspace "Wildebeast"
    architecture "x86_64"
    startproject "Game"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include dirs relative to root (solution)
IncludeDir = {}
IncludeDir["spdlog"] = "Wildebeast/vendor/spdlog/include"
IncludeDir["GLEW"] = "Wildebeast/vendor/GLEW/include"

group "Dependencies"
    include "Wildebeast/vendor/GLEW"

group ""

project "Wildebeast"
    location "Wildebeast"
    kind "StaticLib"
    language "C++"
    staticruntime "on"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

    pchheader "wbpch.h"
    pchsource "Wildebeast/src/wbpch.cpp"

    files 
    {
        "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
    }

    defines
	{
        "_CRT_SECURE_NO_WARNINGS",
        "GLEW_STATIC",
        "GLEW_NO_GLU"
	}

	includedirs
	{
		"%{prj.name}/src",
        "%{IncludeDir.spdlog}",	
        "%{IncludeDir.GLEW}"	
    }

    links
    {
        "GLEW",
		"opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

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
    staticruntime "on"

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
        "Wildebeast/vendor",
		"%{IncludeDir.spdlog}"
    }

    links
    {
        "Wildebeast"
    }

    filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

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
