project "GLEW"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs 
	{
		"include"
	}

	files
	{
		"include/GL/*.h",
		"src/glew.c"
	}

	links
    {
		"opengl32.lib"
    }

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		defines 
		{ 
			"WIN32",
			"GLEW_STATIC",
			"GLEW_NO_GLU",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"