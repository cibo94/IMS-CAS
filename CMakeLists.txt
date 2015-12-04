cmake_minimum_required(VERSION 2.8)
project(cas)

# Compile flags settings #
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic -g")
else (CMAKE_BUILD_TYPE STREQUAL "Release")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O2")
endif ()


add_subdirectory(src)

enable_testing ()
find_program (VAL valgrind)
if (NOT EXISTS ${VAL})
    message (WARNING "Valgrind is not available! running tests without it ...")
    set (VALGRIND)
else (EXISTS ${VAL})
    set (VALGRIND ${VAL} -v --leak-check=full)
endif ()


add_subdirectory(tests)
