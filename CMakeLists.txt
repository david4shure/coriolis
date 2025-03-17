cmake_minimum_required(VERSION 3.10)
project(CoriolisEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_OSX_ARCHITECTURES "arm64")

# Ensure compile_commands.json is generated
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find all source files automatically
file(GLOB_RECURSE SOURCES src/*.cpp)

# Ensure there are source files before creating the library
if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in src/ directory!")
endif()

# Create the static library
add_library(CoriolisEngine STATIC ${SOURCES})

# Add the include directory so headers can be included without relative paths
target_include_directories(CoriolisEngine PUBLIC include)

# Add compiler warnings
target_compile_options(CoriolisEngine PRIVATE -Wall -Wextra -Wpedantic -fsanitize=address,undefined)
target_link_libraries(CoriolisEngine PRIVATE -fsanitize=address,undefined)

# Enable testing and add tests directory
enable_testing()
add_subdirectory(tests)
add_subdirectory(examples)
