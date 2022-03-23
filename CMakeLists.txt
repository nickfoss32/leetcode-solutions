cmake_minimum_required(VERSION 3.23)

project(leetcode)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
	add_compile_definitions(DEBUG)
endif()

add_executable(0001-Two-Sum apps/0001-Two-Sum.cpp)
add_executable(0002-Add-Two-Numbers apps/0002-Add-Two-Numbers.cpp)
add_executable(0003-Longest-Substring-Without-Repeating-Characters apps/0003-Longest-Substring-Without-Repeating-Characters.cpp)
add_executable(0658-Find-K-Closest-Elements apps/0658-Find-K-Closest-Elements.cpp)
