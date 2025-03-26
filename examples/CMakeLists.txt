cmake_minimum_required(VERSION 3.10)
project(CoriolisEngineExamples VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_OSX_ARCHITECTURES "arm64")

# Ensure compile_commands.json is generated
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find all source files automatically
file(GLOB_RECURSE SOURCES *.cpp)

# Ensure there are source files before creating the library
if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in examples/ directory!")
endif()

# ⚠️ **DEFINE THE LIBRARY BEFORE ADDING INCLUDES AND LINKING**
add_library(CoriolisEngineExamples STATIC ${SOURCES})

# Compiler warnings
target_compile_options(CoriolisEngineExamples PRIVATE -Wall -Wextra -Wpedantic)

# Fetch raylib **after defining the library**
include(FetchContent)

FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(raylib)

# Explicitly add raylib's include directories
target_include_directories(CoriolisEngineExamples PRIVATE ${raylib_SOURCE_DIR}/src)

target_include_directories(CoriolisEngineExamples PUBLIC ${CoriolisEngine_SOURCE_DIR}/include)

# Link raylib properly
target_link_libraries(CoriolisEngineExamples PRIVATE raylib CoriolisEngine)

# Ensure executable is linked properly
add_executable(vector vector.cpp)
add_executable(particle particle.cpp)
add_executable(particle_3_d particle_3_d.cpp)
add_executable(fireworks fireworks.cpp)

target_link_libraries(vector PRIVATE CoriolisEngineExamples raylib)
target_link_libraries(particle PRIVATE CoriolisEngineExamples raylib)
target_link_libraries(particle_3_d PRIVATE CoriolisEngineExamples raylib)
target_link_libraries(fireworks PRIVATE CoriolisEngineExamples raylib)
