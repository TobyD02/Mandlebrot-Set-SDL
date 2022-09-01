cmake_minimum_required(VERSION 3.21)
project(project)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(project ${SOURCES})

include_directories(/usr/local/Cellar/sdl2/2.0.22/include/SDL2)
include_directories(/usr/local/Cellar/sdl2_image/2.6.0_1/include/SDL2)
include_directories(src/)

find_library(SDL2 SDl2 /usr/local/Cellar/sdl2/2.0.22/lib)
find_library(SDL2_image SDL2_image /usr/local/Cellar/sdl2_image/2.6.0_1/lib)
target_link_libraries(project LINK_PUBLIC ${SDL2} ${SDL2_image})
