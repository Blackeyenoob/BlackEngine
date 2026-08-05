project "SandBox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	defines
	{
		"GLFW_INCLUDE_NONE",
		"BK_NO_SCRIPTING",
		"BK_NO_PHYSICS",
		"BK_NO_FONT",
		"BK_NO_YAML",
		"BK_NO_VULKAN",
		"BK_NO_IMGUIZMO"
	}

	includedirs
	{
		"../Black/src",
		"../Black/vendor",
		"../Black/vendor/spdlog/include",
		"../Black/vendor/GLFW/include",
		"../Black/vendor/glad/include",
		"../Black/vendor/glm",
		"../Black/vendor/ImGui",
		"../Black/vendor/ImGui/backends",
		"../Black/vendor/entt/include",
		"../Black/vendor/stb_image"
	}

	links
	{
		"Black",
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	libdirs
	{
		"../bin/" .. outputdir .. "/Black",
		"../Black/vendor/GLFW/bin/" .. outputdir .. "/GLFW",
		"../bin/" .. outputdir .. "/Glad"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines { "BK_DEBUG", "BK_ENABLE_ASSERTS" }
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "BK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "BK_DIST"
		runtime "Release"
		optimize "on"
