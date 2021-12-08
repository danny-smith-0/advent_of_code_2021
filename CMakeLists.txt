cmake_minimum_required (VERSION 3.14)
project (advent_of_code_2021)

add_subdirectory(ext/aoc_utils)

add_executable ( aoc
    # main.cpp
    # day5.cpp
    # day6.cpp
	source/day7.cpp
)

target_include_directories ( aoc
    PUBLIC
    include
)