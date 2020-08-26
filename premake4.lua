
solution "GameEngine"

    configurations { "Debug", "Release" }

    project "GameEngine"
        kind "ConsoleApp"
        language "C++"
        files { "source/**.hpp", "source/**.h", "source/**.cpp" }

        configuration "Debug"
            defines { "DEBUG" }
            flags { "Symbols" }

        configuration "Release"
            defines { "NDEBUG" }
            flags { "Optimize" }
