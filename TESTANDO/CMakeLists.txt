cmake_minimum_required(VERSION 3.10)
project(TESTANDO)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)



add_executable(TESTANDO
        CMakeLists.txt
        source/main.cpp
        header/Includes.h
        header/Sprite.h
        header/Shader.h)

find_package(PkgConfig REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_library(Cocoa REQUIRED)
find_library(CoreVideo REQUIRED)
find_library(IOKit REQUIRED)
find_package(GLFW3 REQUIRED)

target_link_libraries(TESTANDO  /usr/local/lib/libglfw.3.2.dylib ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
target_include_directories(TESTANDO PRIVATE ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} /usr/local/include/glm)
