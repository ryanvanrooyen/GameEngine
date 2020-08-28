
configuration "macosx"
    -- OS X frameworks need the extension to be handled properly
    links { "Cocoa.framework", "OpenGL.framework", "IOKit.framework" }

workspace "GameEngine"

    cppdialect "C++17"
    configurations { "Debug", "Release", "Dist" }
    architecture "x64"
    buildoptions { "-Wall" }
    includedirs {
        "vendor/spdlog/include",
        "vendor/glfw/include",
        "vendor/glad",
        "vendor/imgui",
        "vendor/glm",
        "vendor/stb"
    }
    libdirs {
        "vendor/glfw/build",
        "vendor/glad"
    }
    links { "glfw3", "glad" }

    project "GameEngine"
        kind "WindowedApp"
        language "C++"
        targetdir "bin/"
        files {
            "source/**.hpp",
            "source/**.h",
            "source/**.cpp",
            "tests/**.hpp",
            "tests/**.cpp",
            "vendor/stb/**.cpp",
            "vendor/imgui/*.cpp",
            "vendor/imgui/examples/imgui_impl_glfw.cpp",
            "vendor/imgui/examples/imgui_impl_opengl3.cpp",
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        flags "FatalWarnings"
        optimize "On"

    filter "configurations:Dist"
        defines { "DIST" }
        flags "FatalWarnings"
        optimize "On"
