cmake_minimum_required(VERSION 3.24)

project(Engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/vendor/SDL/include)

set(SDL_SHARED OFF CACHE BOOL "Build SDL shared library" FORCE)
set(SDL_STATIC ON CACHE BOOL "Build SDL static library" FORCE)
# Add SDL3 as a subdirectory and build it
add_subdirectory(vendor/SDL)

# Gather all .cpp files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Create executable
add_executable(Engine ${SOURCES})

# Link SDL3 statically
target_link_libraries(Engine PRIVATE SDL3::SDL3)
