
require "premake-ninja/ninja"


newaction {
    trigger = "clean",
    description = "Clean all build files and directories",
    execute = function()
        print("Cleaning build files...")
        os.rmdir("bin")
        os.rmdir("bin-int")

         -- Remove Ninja build files
        os.execute("find . -name '*.ninja' -delete") -- Run Ninja's clean tool
        os.remove(".ninja_log")      -- Ninja's log file
        os.remove(".ninja_deps")     -- Ninja's dependency file


        print("Clean complete!")
    end
}


workspace "Sparkle"
    
    architecture("x86_64")
    cppdialect("C++20")
    staticruntime("on")
   
    configurations { "Release", "Debug" }

    outputdir = "%{cfg.buildcfg}/%{cfg.system}-%{cfg.architecture}/"

    project("Sparkle")
      location("Sparkle")
      kind("StaticLib")
      language("C++")

      targetdir("bin/" .. outputdir .. "%{prj.name}")
      objdir("bin-int/" .. outputdir .. "%{prj.name}")

      files({
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/*.h",
      })

      includedirs({})

      filter("system:windows")
          systemversion("latest")

      filter("configurations:Debug")
          defines("SPRK_DEBUG")
          runtime("Debug")
          symbols("on")

      filter("configurations:Release")
          defines("SPRK_RELEASE")
          runtime("Release")
          optimize("on")

    project("Application")
        location("Application")
        kind("ConsoleApp")
        language("C++")

        targetdir("bin/" .. outputdir .. "%{prj.name}")
        objdir("bin-int/" .. outputdir .. "%{prj.name}")

        files({
          "%{prj.name}/src/**.h",
          "%{prj.name}/src/**.cpp",
        })

        includedirs({
          "Sparkle/src"
        })

        links({
          "Sparkle",
        })

        filter("system:windows")
            systemversion("latest")

        filter("configurations:Debug")
            defines("SPRK_DEBUG")
            runtime("Debug")
            symbols("on")

        filter("configurations:Release")
            defines("SPRK_RELEASE")
            runtime("Release")
            optimize("on")


        
        postbuildcommands {
            ("bin/" .. outputdir .. "%{prj.name}/%{prj.name}")
        }

