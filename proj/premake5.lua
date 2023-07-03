include "dependencies.lua"

workspace "Lolibox"
	architecture "x86_64"
	startproject "ImageProcessor"

	configurations
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Lolibox/vendor/glad.lua"
include "Lolibox/vendor/sdl2.lua"
include "Lolibox/vendor/imgui.lua"
include "Lolibox/vendor/implot.lua"
filter "system:windows"
	include "Lolibox/vendor/sdl2_main.lua"
filter {}

include "Lolibox"
include "ImageProcessor"
