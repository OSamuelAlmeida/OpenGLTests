cmake_minimum_required(VERSION 3.10)

project(OpenGLLearn VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(glfw3 REQUIRED)

file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/vendor/glad)
    message(FATAL_ERROR "glad not found. Download it from https://glad.dav1d.de/ and extract it to ${CMAKE_SOURCE_DIR}/vendor/glad")
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/vendor/stb)
    message(FATAL_ERROR "stb not found. Copy it from https://github.com/nothings/stb and set it up on ${CMAKE_SOURCE_DIR}/vendor/stb")
endif()


add_executable(${PROJECT_NAME} ${PROJECT_SOURCES}
    vendor/glad/src/glad.c vendor/stb/src/stb_image.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_SOURCE_DIR}/vendor/stb/include
    ${CMAKE_SOURCE_DIR}/include
)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)