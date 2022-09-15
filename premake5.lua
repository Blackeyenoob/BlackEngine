workspace "Black"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "Black/vendor/GLFW/include"
 
include "Black/vendor/GLFW"

project "Black"
    location "Black"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "bkpch.h"
    pchsource "Black/src/bkpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "10.0.19041.0"

        defines
        {
            "BK_PLATFORM_WINDOWS",
            "BK_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

        filter "configurations:Debug"
            defines "BK_DEBUG"
            symbols "On"

        filter "configurations:Release"
            defines "BK_RELEASE"
            optimize "On"

        filter "configurations:Dist"
            defines "BK_DIST"
            optimize "On"

project "Sandbox"
    location "Sandbox"
    
    kind "ConsoleApp"

    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
       "Black/vendor/spdlog/include",
       "Black/src;"
    }

    links
    {
        "Black"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "10.0.19041.0"

        defines
        {
            "BK_PLATFORM_WINDOWS"
        }

        filter "configurations:Debug"
            defines "BK_DEBUG"
            symbols "On"

        filter "configurations:Release"
            defines "BK_RELEASE"
            optimize "On"

        filter "configurations:Dist"
            defines "BK_DIST"
            optimize "On"