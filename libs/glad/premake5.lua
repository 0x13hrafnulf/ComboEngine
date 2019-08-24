project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    systemversion "latest"
    
    targetdir ("build/" .. outputdir .. "/%{prj.name}")
    objdir ("build-interm/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }

    includedirs
    {
        "include"
    }
   

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"