project "ImageProcessor"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

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

	includedirs
	{
		"src",
        "%{IncludeDir.GLM}",
		"%{IncludeDir.STB}",
		"%{IncludeDir.SDL2}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImPlot}",
		"%{IncludeDir.eventpp}",
		"%{wks.location}/Lolibox/src"
	}

	links
	{
		"ImPlot",
        "Lolibox"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
