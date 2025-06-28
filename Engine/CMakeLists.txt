cmake_minimum_required(VERSION 3.24)

project(Engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/vendor/SDL/include)
include_directories(${PROJECT_SOURCE_DIR}/vendor/imgui)


set(SDL_SHARED OFF CACHE BOOL "Build SDL shared library" FORCE)
set(SDL_STATIC ON CACHE BOOL "Build SDL static library" FORCE)

# Add SDL3 as a subdirectory and build it
add_subdirectory(vendor/SDL)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/imgui)

# Gather all .cpp files
file(GLOB_RECURSE SOURCES src/*.cpp)

find_package(Vulkan REQUIRED)

# Create executable
add_executable(Engine ${SOURCES}
        include/Sparkle/Log.h
        include/Sparkle/Window.h
        src/Window.cpp
        include/Sparkle/Engine.h
        src/Engine.cpp
        include/skpch.h
        include/Sparkle/EventSystem.h
        src/EventSystem.cpp
        include/Sparkle/Events.h
        include/Sparkle/InputCodes.h
        include/Sparkle/InputSystem.h
        src/InputSystem.cpp
        include/Sparkle/Layer.h
        include/Sparkle/LayerStack.h
        src/LayerStack.cpp
        include/Sparkle.h
        include/Sparkle/ImGuiLayer.h
        src/ImGuiLayer.cpp
        src/Renderer.cpp
        include/Sparkle/Renderer.h)
target_precompile_headers(Engine PRIVATE include/skpch.h)

# Link SDL3 statically
target_link_libraries(Engine PRIVATE Vulkan::Vulkan SDL3::SDL3 imgui spdlog::spdlog_header_only)
