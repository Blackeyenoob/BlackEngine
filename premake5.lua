include "Dependencies.lua"

workspace "Black"
	architecture "x86_64"
	startproject "SandBox"

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

group "Dependencies"
	include "Black/vendor/GLFW"
	include "Black/vendor/glad"
group ""

group "Core"
	include "Black"
group ""

group "Misc"
	include "SandBox"
group ""
