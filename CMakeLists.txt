cmake_minimum_required (VERSION 3.14)
project (advent_of_code_2021)

add_executable ( aoc
    main.cpp
)

target_include_directories ( aoc
    PUBLIC
    include
)