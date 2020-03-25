
cmake_minimum_required(VERSION 3.10)

project(hello-opencv)

if (NOT gc_project_path)
    set(gs_project_path ${CMAKE_CURRENT_SOURCE_DIR}/../..)
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")

include(local.config.cmake)
include(utils.cmake)
include(fs.cmake)

include(opencv.cmake)

add_subdirectory(hello)

add_subdirectory(examples)

add_subdirectory(tools)
