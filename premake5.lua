

configuration "macosx"
    -- OS X frameworks need the extension to be handled properly
    links { "Cocoa.framework", "OpenGL.framework", "IOKit.framework" }
    defines { "PLATFORM_MAC" }


configuration "windows"
    defines { "PLATFORM_WINDOWS" }
    debugdir "$(SolutionDir)" --> Set working dir for VS to root folder


workspace "GameEngine"
    configurations { "Debug", "Release", "Dist" }
    startproject "EngineTests"
    architecture "x64"
    systemversion "latest"
    targetdir "bin/"
    objdir "bin/obj/"
    staticruntime "On" --> Sets <RuntimeLibrary> to "MultiThreaded" in VS

    filter "configurations:Debug"
        defines { "DEBUG" }
        flags { "MultiProcessorCompile" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        flags { "MultiProcessorCompile", "FatalWarnings" }
        optimize "On"

    filter "configurations:Dist"
        defines { "DIST" }
        flags { "MultiProcessorCompile", "FatalWarnings" }
        optimize "Speed"


group "Vendor"

    project "Glad"
        kind "StaticLib"
        language "C"
        location "vendor"
        targetdir "bin/obj/%{cfg.buildcfg}"
        files {
            "vendor/glad/**.c",
        }
        includedirs {
            "vendor/glad",
        }


    project "GLFW"
        kind "StaticLib"
        language "C"
        targetdir "bin/obj/%{cfg.buildcfg}"
        location "vendor"
        files {
            "vendor/glfw/src/internal.h",
            "vendor/glfw/src/mappings.h",
            "vendor/glfw/src/glfw_config.h",
            "vendor/glfw/include/GLFW/glfw3.h",
            "vendor/glfw/include/GLFW/glfw3native.h",
            "vendor/glfw/src/context.c",
            "vendor/glfw/src/init.c",
            "vendor/glfw/src/input.c",
            "vendor/glfw/src/monitor.c",
            "vendor/glfw/src/vulkan.c",
            "vendor/glfw/src/window.c"
        }

        filter "system:macosx"
            files {
                "vendor/glfw/src/cocoa_init.m",
                "vendor/glfw/src/cocoa_joystick.m",
                "vendor/glfw/src/cocoa_monitor.m",
                "vendor/glfw/src/cocoa_window.m",
                "vendor/glfw/src/cocoa_time.c",
                "vendor/glfw/src/posix_thread.c",
                "vendor/glfw/src/nsgl_context.m",
                "vendor/glfw/src/egl_context.c",
                "vendor/glfw/src/osmesa_context.c",
            }
            defines {
                "_GLFW_COCOA"
            }

        filter "system:linux"
            pic "On"
            files {
                "vendor/glfw/src/x11_init.c",
                "vendor/glfw/src/x11_monitor.c",
                "vendor/glfw/src/x11_window.c",
                "vendor/glfw/src/xkb_unicode.c",
                "vendor/glfw/src/posix_time.c",
                "vendor/glfw/src/posix_thread.c",
                "vendor/glfw/src/glx_context.c",
                "vendor/glfw/src/egl_context.c",
                "vendor/glfw/src/osmesa_context.c",
                "vendor/glfw/src/linux_joystick.c"
            }
            defines {
                "_GLFW_X11"
            }

        filter "system:windows"
            files {
                "vendor/glfw/src/win32_init.c",
                "vendor/glfw/src/win32_joystick.c",
                "vendor/glfw/src/win32_monitor.c",
                "vendor/glfw/src/win32_time.c",
                "vendor/glfw/src/win32_thread.c",
                "vendor/glfw/src/win32_window.c",
                "vendor/glfw/src/wgl_context.c",
                "vendor/glfw/src/egl_context.c",
                "vendor/glfw/src/osmesa_context.c"
            }
            defines {
                "_GLFW_WIN32",
                "_CRT_SECURE_NO_WARNINGS"
            }


    project "ImGui"
        kind "StaticLib"
        language "C++"
        location "vendor"
        targetdir "bin/obj/%{cfg.buildcfg}"
        files {
            "vendor/imgui/*.cpp",
            "vendor/imgui/examples/imgui_impl_glfw.cpp",
            "vendor/imgui/examples/imgui_impl_opengl3.cpp",
        }
        includedirs {
            "vendor/glfw/include",
            "vendor/glad",
            "vendor/imgui",
        }
               

    project "Utils"
        kind "StaticLib"
        language "C++"
        location "vendor"
        targetdir "bin/obj/%{cfg.buildcfg}"
        files {
            "vendor/stb/**.cpp",
        }
        includedirs {
            "vendor/stb"
        }
               

group ""

    project "Engine"
        kind "StaticLib"
        location "Engine"
        language "C++"
        cppdialect "C++17"
        buildoptions { "-Wall" }
        targetdir "bin/obj/%{cfg.buildcfg}"
        pchheader "EngineCommon.h"
        pchsource "Engine/EngineCommon.cpp"
        files {
            "Engine/**.h*",
            "Engine/**.cpp",
        }
        includedirs {
            "Engine",
            "vendor/spdlog/include",
            "vendor/glfw/include",
            "vendor/glad",
            "vendor/imgui",
            "vendor/glm",
            "vendor/stb"
        }


    project "EngineTests"
        kind "ConsoleApp"
        location "EngineTests"
        language "C++"
        cppdialect "C++17"
        buildoptions { "-Wall" }
        files {
            "EngineTests/**.h*",
            "EngineTests/**.cpp",
        }
        includedirs {
            "Engine",
            "EngineTests",
            "vendor/spdlog/include",
            "vendor/imgui",
            "vendor/glm",
        }
        links { "Engine", "GLFW", "Glad", "ImGui", "Utils" }
