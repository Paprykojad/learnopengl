cmake_minimum_required(VERSION 3.28.3)
project(learnopengl)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g")        # Add debug symbols
set(CMAKE_CXX_FLAGS_RELEASE "-O3")    # Optimize for Release
set(CMAKE_BUILD_TYPE Debug)           # Default build type is Debug


add_executable(learnopengl ${CMAKE_SOURCE_DIR}/src/main.cpp
        src/Shader.cpp
        src/Shader.h
        dependencies/headers/stb_image.h
        dependencies/src/stb_image.cpp)
target_link_directories(learnopengl PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/libraries)
target_include_directories(learnopengl PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/headers)

target_link_libraries(learnopengl glfw3 glad )

# target_compile_options(learnopengl PUBLIC $<$<CONFIG:Debug>:--debug>)


add_library(glad STATIC ${CMAKE_SOURCE_DIR}/dependencies/src/glad.c)
target_include_directories(glad PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/headers)
