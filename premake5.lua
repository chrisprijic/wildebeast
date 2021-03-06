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
IncludeDir["d3dx12"] = "Wildebeast/vendor/d3dx12/include"
IncludeDir["Vulkan"] = "$(VULKAN_SDK)/include"
IncludeDir["ImGui"] = "Wildebeast/vendor/imgui"

group "Dependencies"
    include "Wildebeast/vendor/GLEW"
    include "Wildebeast/vendor/imgui"

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
        "%{IncludeDir.GLEW}",
        "%{IncludeDir.Vulkan}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "GLEW",
		"opengl32.lib",
        "$(VULKAN_SDK)/lib/vulkan-1.lib",
        "ImGui"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        links
        {
            "Xinput9_1_0.lib",
            "d3dcompiler", 
            "dxguid", 
            "d3d12", 
            "dxgi"
        }

        includedirs 
        {
            "%{IncludeDir.d3dx12}"
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
		"%{IncludeDir.spdlog}",
        "%{IncludeDir.GLEW}",
        "%{IncludeDir.Vulkan}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "Wildebeast"
    }

    filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

        includedirs 
        {
            "%{IncludeDir.d3dx12}"
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
