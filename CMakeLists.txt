# Minimum required version of CMake
cmake_minimum_required(VERSION 3.15)

# Project name and version
project(obj_loader VERSION 1.0)

# Specify C++ standard (can be set to 11, 14, 17, etc.)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files for your project
set(SOURCES
    src/main.cpp
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Set MinGW-specific configurations
if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
endif()

# Automatically include MinGW directories
include_directories(
    ${CMAKE_SYSTEM_INCLUDE_PATH}
)

add_definitions(-DGLEW_STATIC)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME}
    -lglew32s
    OpenGL::GL
    -lglfw3
    
)

# Output executable to a specific folder
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)