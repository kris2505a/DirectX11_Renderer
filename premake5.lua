project "Renderer"
    location "Renderer"
    kind "StaticLib"
    language "C++"

    cppdialect "C++20"
    staticruntime "Off"
    systemversion "latest"

    targetdir ("binaries/" .. outputDir .. "/%{prj.name}")
    objdir    ("intermediate/" .. outputDir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/include",
        "%{prj.name}/src"
    }

    libdirs {

    }

    links {

        "d3d11.lib",
        "dxgi.lib",
        "d3dcompiler.lib"
    }

    defines {
        "PLATFORM_WINDOWS"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        defines { "_DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "On"