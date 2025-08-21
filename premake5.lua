workspace "Mira"
    architecture "x64"

    configurations {
        "Debug", "Release"
    }
	
	-- startproject "Sandbox"
	
outputDir = "%{cfg.buildcfg}-%{cfg.architecture}" 

IncludeDirectories = {}

IncludeDirectories["SFML"] = "MiraEngine/thirdparty/SFML"


project "MiraEngine"
    location "MiraEngine"
    kind "sharedLib"
    language "C++"
    staticruntime "Off"


    targetdir("binaries/" .. outputDir .. "/%{prj.name}")
    objdir("intermediate/" .. outputDir .. "/%{prj.name}")
	
	pchheader "MiraPreCompHeader.h"
	pchsource "MiraEngine/sources/MiraPreCompHeader.cpp"

    files {
        "%{prj.name}/sources/**.h",
        "%{prj.name}/sources/**.cpp"
    }

    includedirs {
        "%{prj.name}/sources",
		"%{IncludeDirectories.SFML}/include"
    }

    libdirs {
		"%{IncludeDirectories.SFML}/lib"
    }
    
    links {
        "opengl32.lib",
		"winmm.lib",
		"gdi32.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "Off"
        systemversion "latest"

    defines {
        "API_ENGINE"
    }
	
	postbuildcommands {
		"{COPY} %{cfg.buildtarget.abspath} ../binaries/" .. outputDir .. "/Sandbox"
	}


    filter "configurations:Debug"
        links {
            "sfml-audio-d.lib",
            "sfml-graphics-d.lib",
            "sfml-window-d.lib",
            "sfml-main-d.lib",
            "sfml-system-d.lib"
        }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        links {
            "sfml-audio.lib",
            "sfml-graphics.lib",
            "sfml-window.lib",
            "sfml-main.lib",
            "sfml-system.lib"
        }
        runtime "Release"
        optimize "On"

-- project "Sandbox"
--     location "Sandbox"
--     kind "consoleApp"
--     language "C++"
--     staticruntime "Off"


--     targetdir("binaries/" .. outputDir .. "/%{prj.name}")
--     objdir("intermediate/" .. outputDir .. "/%{prj.name}")

--     files {
--         "%{prj.name}/sources/**.h",
--         "%{prj.name}/sources/**.cpp"
--     }

--     includedirs {
--         "%{IncludeDirectories.SFML}/include",
--         "%{prj.name}/sources",
-- 		"MiraEngine/sources/"
--     }

--     libdirs {
-- 		"%{IncludeDirectories.SFML}/lib"
--     }
    
--     links {
--         "opengl32.lib",
-- 		"winmm.lib",
-- 		"gdi32.lib",
-- 		"MiraEngine",
--     }

--     filter "system:windows"
--         cppdialect "C++20"
--         staticruntime "Off"
--         systemversion "latest"

--     defines {
	
--     }

--     filter "configurations:Debug" 
--         links {
--             "sfml-audio-d.lib",
--             "sfml-graphics-d.lib",
--             "sfml-window-d.lib",
--             "sfml-main-d.lib",
--             "sfml-system-d.lib"
--         }
--         runtime "Debug"
--         symbols "On"

--     filter "configurations:Release"
--         links {
--             "sfml-audio.lib",
--             "sfml-graphics.lib",
--             "sfml-window.lib",
--             "sfml-main.lib",
--             "sfml-system.lib"
--         }
--         runtime "Release"
--         optimize "On"

	