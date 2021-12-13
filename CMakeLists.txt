cmake_minimum_required (VERSION 3.14)
project (advent_of_code_2021)

add_subdirectory(ext/aoc_utils)

add_executable ( aoc
    # source/day4.cpp
    # source/day5.cpp
    # source/day6.cpp
	# source/day7.cpp
	# source/day8.cpp
	# source/day9.cpp
	# source/day10.cpp
	# source/day11.cpp
	source/day13.cpp
)

target_link_libraries( aoc
    PUBLIC
    aoc_utils
)
