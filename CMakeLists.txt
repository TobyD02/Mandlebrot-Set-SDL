cmake_minimum_required(VERSION 3.21)
project(project)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(project ${SOURCES})

include_directories(/usr/local/Cellar/sdl2/2.0.22/include/SDL2)
include_directories(src/)

find_library(SDL2 SDl2 /usr/local/Cellar/sdl2/2.0.22/lib)
target_link_libraries(project LINK_PUBLIC ${SDL2})
