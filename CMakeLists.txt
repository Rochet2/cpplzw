cmake_minimum_required (VERSION 2.6)
project(cpplzw)

file(GLOB SOURCES src/*.cpp src/*.h)

add_executable(cpplzw ${SOURCES})

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    add_definitions(-D_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wno-long-long -pedantic -std=c++11")
endif ()
