project "SDL2main"
	kind "StaticLib"
	language "C"
	systemversion "latest"

	flags
	{
		"NoRuntimeChecks",
		"NoBufferSecurityCheck"
	}

	vectorextensions "SSE"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs { "sdl2/include" }

	files { "sdl2/src/main/windows/*.c" }	

	systemversion "latest"
	defines
	{
		"_WINDOWS",
		"WIN32"
	}

	filter "configurations:Debug"
		defines
		{
			"_DEBUG"
		}
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines
		{
			"NDEBUG"
		}
		runtime "Release"
		optimize "Speed"
