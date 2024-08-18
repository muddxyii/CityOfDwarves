cmake_minimum_required(VERSION 3.29)
project(OverheadBuilder)

set(CMAKE_CXX_STANDARD 20)

if(APPLE)
    set(SDL2_DIR "/opt/homebrew/lib/cmake/SDL2")
endif()
find_package(SDL2 REQUIRED)

find_package(glm REQUIRED)

add_executable(OverheadBuilder main.cpp
        Engine/Engine.cpp
        Engine/Engine.h
        Engine/Input/Input.cpp
        Engine/Input/Input.h)

target_include_directories(OverheadBuilder PRIVATE ${SDL2_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})
target_link_libraries(OverheadBuilder PRIVATE SDL2::SDL2 glm::glm)