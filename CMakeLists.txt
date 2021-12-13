cmake_minimum_required (VERSION 3.14)
project (advent_of_code_2021)

add_subdirectory(ext/aoc_utils)

add_executable ( aoc
    # source/day04.cpp
    # source/day05.cpp
    # source/day06.cpp
	# source/day07.cpp
	# source/day08.cpp
	# source/day09.cpp
	# source/day10.cpp
	# source/day11.cpp
	source/day12.cpp
	# source/day13.cpp
)

target_link_libraries( aoc
    PUBLIC
    aoc_utils
)
