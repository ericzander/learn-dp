# Recursively find cpp files
file(GLOB_RECURSE SOURCES "*.cpp")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add local includes
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/utils)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain)
