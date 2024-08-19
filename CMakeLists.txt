cmake_minimum_required(VERSION 3.29)
project(CityOfDwarves)

set(CMAKE_CXX_STANDARD 20)

if(APPLE)
    set(SDL2_DIR "/opt/homebrew/lib/cmake/SDL2")
endif()
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

find_package(glm REQUIRED)

add_executable(CityOfDwarves main.cpp
        Engine/Engine.cpp
        Engine/Engine.h
        Engine/Input/Input.cpp
        Engine/Input/Input.h
        Engine/Camera/Camera.cpp
        Engine/Camera/Camera.h)

target_include_directories(CityOfDwarves PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
)
target_link_libraries(CityOfDwarves PRIVATE
        SDL2::SDL2
        SDL2_image::SDL2_image
        glm::glm
)