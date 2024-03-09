cmake_minimum_required(VERSION 3.21)

project(cthash VERSION 1.0 LANGUAGES CXX)

if (PROJECT_IS_TOP_LEVEL)
list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

include(colors)
include(pedantic)

option(CTHASH_TESTS "Enable CTHASH testing" OFF)

if (CTHASH_TESTS)
	option(CTHASH_COVERAGE "Enable CTHASH test-coverage" ON)

	if (CTHASH_COVERAGE)
		include(coverage)
		enable_coverage()
	else()
		message(STATUS "Test coverage measurement is OFF")
	endif()

	add_subdirectory(tests)
else()
	message(STATUS "Tests are disabled")
endif()

option(CTHASH_EXAMPLES "Build CTHASH examples" ON)

if (CTHASH_EXAMPLES)
	add_subdirectory(examples)
endif()

add_executable(example example.cpp)
target_link_libraries(example cthash)

add_executable(checksum checksum.cpp)
target_link_libraries(checksum cthash)
endif()

add_subdirectory(include)
