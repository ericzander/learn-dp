# Specify required version
cmake_minimum_required(VERSION 3.27.6)

# Use C++17
set(CMAKE_CXX_STANDARD 17)

# Init project
project(learn-dp VERSION 1.0 LANGUAGES CXX)

# Set executable output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add subdirectories with instructions (ie CMakeLists.txt)
add_subdirectory(src)

# Get Catch2 for unit testing
include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(catch2)
