cmake_minimum_required(VERSION 3.10)

project(OpenGLLearn VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp 
    vendor/glad/src/glad.c)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/vendor/glad/include
)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)