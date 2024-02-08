cmake_minimum_required(VERSION 3.24)
project(lowris C)

set(CMAKE_C_STANDARD 11)


add_executable(lowris src/main.c)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
include_directories(lowris ${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS})
target_link_libraries(lowris SDL2::SDL2 SDL2_image::SDL2_image)