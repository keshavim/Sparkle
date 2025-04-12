
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

    filter { "toolset:gcc or clang" }
     -- Add custom compiler flags
    buildoptions {
        "-fdiagnostics-color=always",  -- Enable colored diagnostics
        "-fmessage-length=80",        -- Set message length to 80 characters
        "-fno-elide-type",            -- Disable type elision in error messages
        "-fdiagnostics-show-template-tree" -- Show template mismatches as a tree
    }
    filter{}


    configurations { "Release", "Debug" }

    outputdir = "%{cfg.buildcfg}/%{cfg.system}-%{cfg.architecture}/"

    project("Sparkle")
      location("Sparkle")
      kind("StaticLib")
      language("C++")
      staticruntime("on")
      cppdialect("C++20")

      targetdir("bin/" .. outputdir .. "%{prj.name}")
      objdir("bin-int/" .. outputdir .. "%{prj.name}")

      files({
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/*.h",
      })

      includedirs({
          "%{prj.name}/vendor/spdlog/include"
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
        filter{}

        
        postbuildcommands {
            ("bin/" .. outputdir .. "%{prj.name}/%{prj.name}")
        }

