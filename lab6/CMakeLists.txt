cmake_minimum_required(VERSION 3.10)

project(lab6)

add_executable(main main.c)

if (BUILD_STATIC)
    message("Build static")
    add_library(sort STATIC ${lab6})
    add_library(student STATIC ${lab6})
    target_link_libraries(main sort student)
else ()
    message("Build shared")
    add_library(sort SHARED ${lab6})
    add_library(student SHARED ${lab6})
    target_link_libraries(main sort student)
endif()