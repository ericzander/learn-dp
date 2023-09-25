# Specify required version
cmake_minimum_required(VERSION 3.27.6)

# Init project
project(learn-dp VERSION 1.0 LANGUAGES CXX)

# Set executable output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Go to source for code + executable
add_subdirectory(src)
