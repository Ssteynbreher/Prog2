cmake_minimum_required(VERSION 3.10)

project(rgr)

add_executable(main main.c)

if (BUILD_STATIC)
    message("Build static")
    add_library(polybius STATIC polybius.c)
    target_link_libraries(main polybius)
else()
    message("Build shared")
    add_library(polybius SHARED polybius.c)
    target_link_libraries(main polybius)
endif()
