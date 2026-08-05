project "Black"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "bkpch.h"
	pchsource "src/bkpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"vendor/ImGui/imgui.h",
		"vendor/ImGui/imgui.cpp",
		"vendor/ImGui/imgui_draw.cpp",
		"vendor/ImGui/imgui_tables.cpp",
		"vendor/ImGui/imgui_widgets.cpp",
		"vendor/ImGui/imconfig.h",
		"vendor/ImGui/imgui_internal.h",
		"vendor/ImGui/imstb_rect.h",
		"vendor/ImGui/imstb_textedit.h",
		"vendor/ImGui/imstb_truetype.h",
		"vendor/ImGui/backends/imgui_impl_opengl3.h",
		"vendor/ImGui/backends/imgui_impl_glfw.h",
		"vendor/ImGui/misc/cpp/imgui_stdlib.h",
		"vendor/entt/include/entt.hpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"YAML_CPP_STATIC_DEFINE",
		"IMGUI_DEFINE_MATH_OPERATORS",
		"BK_NO_SCRIPTING",
		"BK_NO_PHYSICS",
		"BK_NO_FONT",
		"BK_NO_YAML",
		"BK_NO_VULKAN",
		"BK_NO_IMGUIZMO"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"vendor/GLFW/include",
		"vendor/glad/include",
		"vendor/glm",
		"vendor/stb_image",
		"vendor/ImGui",
		"vendor/ImGui/backends",
		"vendor/entt/include",
		"vendor/filewatch",
		"vendor/yaml-cpp/include"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "files:vendor/ImGui/**.cpp"
		flags { "NoPCH" }

	filter "files:vendor/stb_image/**.cpp"
		flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

		links
		{
		}

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
