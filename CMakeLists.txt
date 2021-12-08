cmake_minimum_required (VERSION 3.14)
project (advent_of_code_2021)

add_subdirectory(ext/aoc_utils)

add_executable ( aoc
    # source/day4.cpp
    # source/day5.cpp
    # source/day6.cpp
	# source/day7.cpp
	source/day8.cpp
)

target_link_libraries( aoc
    PUBLIC
    aoc_utils
)
