
configuration "macosx"
    -- OS X frameworks need the extension to be handled properly
    links { "Cocoa.framework", "OpenGL.framework", "IOKit.framework" }

workspace "GameEngine"

    cppdialect "C++17"
    configurations { "Debug", "Release" }
    flags "FatalWarnings"
    buildoptions { "-Wall" }
    includedirs { "vendor/glfw/include", "vendor/glad", "vendor/imgui", "vendor/glm", "vendor/stb" }
    libdirs { "vendor/glfw/build", "vendor/glad" }
    links { "glfw3", "glad" }

    project "GameEngine"
        kind "WindowedApp"
        language "C++"
        files {
            "source/**.hpp",
            "source/**.h",
            "source/**.cpp",
            "tests/**.hpp",
            "tests/**.cpp",
            "vendor/imgui/**.cpp",
            "vendor/stb/**.cpp",
        }

        configuration "Debug"
            defines { "DEBUG" }
            symbols "On"

        configuration "Release"
            defines { "NDEBUG" }
            optimize "On"

        targetdir "bin/"
