cmake_minimum_required(VERSION 3.28.3)
project(learnopengl)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)

# include_directories(${CMAKE_SOURCE_DIR}/dependencies/headers)

add_executable(learnopengl main.cpp)
target_link_directories(learnopengl PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/libraries)
target_include_directories(learnopengl PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/headers)

target_link_libraries(learnopengl glfw3 glad )

add_library(glad STATIC ${CMAKE_SOURCE_DIR}/dependencies/src/glad.c)
target_include_directories(glad PRIVATE ${CMAKE_SOURCE_DIR}/dependencies/headers)
