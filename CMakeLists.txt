cmake_minimum_required(VERSION 3.23)

project(leetcode)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
	add_compile_definitions(DEBUG)
endif()

add_executable(K-Closest-Elements apps/K-Closest-Elements.cpp)
