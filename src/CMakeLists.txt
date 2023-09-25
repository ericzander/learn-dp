# Recursively find cpp files
file(GLOB_RECURSE SOURCES "*.cpp")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add includes
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
