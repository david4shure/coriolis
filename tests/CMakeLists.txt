cmake_minimum_required(VERSION 3.10)
project(CoriolisEngineTests VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ensure there are source files before creating the library
if(NOT SOURCES)
    message(FATAL_ERROR "No tests found in tests/ directory!")
endif()

# Download and configure GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(run_tests main.cpp test_vector.cpp)

# Link test executable with GoogleTest and the project library
target_link_libraries(run_tests PRIVATE CoriolisEngine gtest gtest_main)

# Register tests
include(GoogleTest)
gtest_discover_tests(run_tests)
