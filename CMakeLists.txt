
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-narrowing -Wa,-mbig-obj")

#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-narrowing -std=c++11 -Wa,-mbig-obj")

# cmake c++ hello1


cmake_minimum_required(VERSION 3.10)

project(hello-cmake)

set(gs_project_path ${CMAKE_CURRENT_SOURCE_DIR})

include(build/cmake/local.config.cmake)
include(build/cmake/utils.cmake)
include(build/cmake/fs.cmake)

add_subdirectory(build/cmake)
