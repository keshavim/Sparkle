


newaction {
    trigger = "clean",
    description = "Clean all build files and directories",
    execute = function()
        print("Cleaning build files...")
       os.execute("make clean")
        os.rmdir("bin")
        os.rmdir("bin-int")
        

        os.execute("find . -name 'Makefile' -delete")


        print("Clean complete!")
    end
}



workspace "Sparkle"
    architecture("x86_64")

    systemversion("latest")

    filter("system:windows")
        defines("SPRK_PLATFORM_WINDOWS")
    filter("system:linux")
        toolset "clang"
        defines("SPRK_PLATFORM_LINUX")
    filter{}

    configurations { "Debug", "Releasee" }

    outputdir = "%{cfg.buildcfg}/%{cfg.system}-%{cfg.architecture}/"


    --include dirs relitive to route 
    IncludeDirs = {}
    IncludeDirs["Glfw"] = "Sparkle/vendor/Glfw/inlcude"


    include "Sparkle/vendor/Glfw"


    project("Sparkle")
      location("Sparkle")
      kind("StaticLib")
      language("C++")
      staticruntime("on")
      cppdialect("C++20")



      targetdir("bin/" .. outputdir .. "%{prj.name}")
      objdir("bin-int/" .. outputdir .. "%{prj.name}")

        pchheader "sprkpch.h"
        pchsource "%{prj.name}/src/sprkpch.cpp"

      files({
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
      })

      includedirs({
          "%{prj.name}/src",
          "%{prj.name}/vendor/spdlog/include",
          "%{IncludeDirs.Glfw}"
      })

      links {
        "Glfw",
        "GL",
    
      }

      filter("system:windows")
        links {
          "opengl32.lib"
        }
      filter("system:linux")
        links {
          "GL"
        "X11",
        "dl",
        "pthread",
        "m"
        }

      -- filter { "toolset:gcc or clang" }
      --   buildoptions {
      --       "-Wall",
      --       "-Wextra",
      --       "-fdiagnostics-color=always",
      --   }

      filter("configurations:Debug")
          defines("SPRK_DEBUG")
          runtime("Debug")
          symbols("on")

      filter("configurations:Release")
          defines("SPRK_RELEASE")
          runtime("Release")
          optimize("on")
      filter{}

    project("Application")
        location("Application")
        kind("ConsoleApp")
        language("C++")
        cppdialect("C++20")
        staticruntime("on")

        targetdir("bin/" .. outputdir .. "%{prj.name}")
        objdir("bin-int/" .. outputdir .. "%{prj.name}")

        files
        ({
          "%{prj.name}/src/**.h",
          "%{prj.name}/src/**.cpp",
        })

        includedirs({
          "Sparkle/vendor/spdlog/include",
          "Sparkle/src"
        })

        links({
          "Sparkle",
          "Glfw"
        })


        -- filter { "toolset:gcc or clang" }
        --   buildoptions {
        --       "-Wall",
        --       "-Wextra",
        --       "-fdiagnostics-color=always",
        --   }

        filter("configurations:Debug")
            defines("SPRK_DEBUG")
            runtime("Debug")
            symbols("on")

        filter("configurations:Release")
            defines("SPRK_RELEASE")
            runtime("Release")
            optimize("on")
        filter{}

        
        postbuildcommands {
            "%{wks.location}/bin/" .. outputdir .. "/%{prj.name}/%{prj.name}"
        }

