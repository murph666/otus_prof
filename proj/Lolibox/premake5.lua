project "Lolibox"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"
	pchsource "src/pch.cpp"

    vpaths
    {
        ["Headers"] = {"**.h", "**.hpp"},
        ["Sources"] = {"**.c", "**.cpp"}
    }

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"src",
        "%{IncludeDir.GLM}",
		"%{IncludeDir.STB}",
		"%{IncludeDir.SDL2}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.eventpp}"
	}

	links
	{
		"SDL2",
		"GLAD",
		"ImGui",
		"Dwmapi.lib", -- Windows HWND config stuff (OS Build 22000)
		"opengl32.lib"
	}

	linkoptions
	{
		"/NODEFAULTLIB"
	}

	filter "system:windows"
		systemversion "latest"
		links
		{
			"SDL2main"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
