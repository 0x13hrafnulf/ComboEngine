workspace "Combo"
    architecture "x86_64"
    startproject "App"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
        
IncludeDir = {}
IncludeDir["SDL2"] = "libs/SDL2/include"
IncludeDir["GLAD"] = "libs/glad/include"
IncludeDir["ImGui"] = "libs/imgui"
IncludeDir["GLM"] = "libs/glm"


group "Dependencies"
    include "libs/glad"
    include "libs/imgui"
group ""




project "Combo"
    location "src/Combo"
    kind "StaticLib" --StaticLib/SharedLib
    language "C++"
    cppdialect "C++11" --C++11/14/17
    staticruntime "on"
    systemversion "latest"

    targetdir ("build/" .. outputdir .. "/%{prj.name}")
    objdir ("build-interm/" .. outputdir .. "/%{prj.name}")

    pchheader "combopch.h"
    pchsource "src/Combo/combopch.cpp"

    files
    {
        "src/%{prj.name}/**.h",
        "src/%{prj.name}/**.cpp",
        "libs/glm/glm/**.hpp",
        "libs/glm/glm/**.inl"
    }
    
    removefiles("src/%{prj.name}/not_used/**")
    
    includedirs
    {
        "src/%{prj.name}/",
        "libs/spdlog/include/",
        "libs/",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.GLM}",
      
    }
    links 
    {
        "Glad",
        "ImGui"
    }
    
    filter {"system:linux"}
        pic "on"
        buildoptions{
            "`sdl2-config --cflags --libs`", -- "-lSDL2", "-lSDL2main",
            "-lGL","-lGLU",
            "-lGLEW", "-ldl",
            "-lm", "-lXrandr", "-lXi", "-lX11", "-lXxf86vm", "-lpthread"
        }
        linkoptions{
            "`sdl2-config --cflags --libs`", -- "-lSDL2", "-lSDL2main",
            "-lGL","-lGLU",
            "-lGLEW", "-ldl",
            "-lm", "-lXrandr", "-lXi", "-lX11", "-lXxf86vm", "-lpthread"
        }

   filter "system:windows" --includedirs {"%{IncludeDir.SDL2}"} libdirs {"%{LibDir.SDL2}"}
        links{
            "opengl32.lib"
        }

  
    filter "configurations:Debug"
		defines "COMBO_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "COMBO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "COMBO_DIST"
		runtime "Release"
		optimize "on"
        
        
project "Application"
    location "src/Application"    
    kind "ConsoleApp" --StaticLib/SharedLib
    language "C++"
    cppdialect "C++11" --C++11/14/17
    staticruntime "on"
    systemversion "latest"

    targetdir ("build/" .. outputdir .. "/%{prj.name}")
    objdir ("build-interm/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/%{prj.name}/**.h",
        "src/%{prj.name}/**.cpp"
    }

    includedirs
    {
        "src/%{prj.name}/",
        "src/",
        "libs/spdlog/include/",
        "libs/",
        "%{IncludeDir.GLM}",
    }

    links
    {
        "Combo"
    }
    filter {"system:linux"}
        links 
        { 
            "Glad",
            "ImGui"
            
        }
        buildoptions{
            "`sdl2-config --cflags --libs`", -- "-lSDL2", "-lSDL2main",
            "-lGL","-lGLU",
            "-lGLEW", "-ldl", 
            "-lm", "-lXrandr", "-lXi", "-lX11", "-lXxf86vm", "-lpthread"
        }
        linkoptions{
            "`sdl2-config --cflags --libs`", -- "-lSDL2", "-lSDL2main",
            "-lGL","-lGLU",
            "-lGLEW", "-ldl",
            "-lm", "-lXrandr", "-lXi", "-lX11", "-lXxf86vm", "-lpthread"
        }

    filter "configurations:Debug"
		defines "COMBO_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "COMBO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "COMBO_DIST"
		runtime "Release"
		optimize "on"
        