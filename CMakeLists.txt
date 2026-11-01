cmake_minimum_required(VERSION 3.16)

project(SkipLists LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(skip_lists main.cpp)
target_compile_features(skip_lists PRIVATE cxx_std_20)
target_compile_options(skip_lists PRIVATE -Wall -Wextra)

add_custom_target(check_header
	COMMAND ${CMAKE_CXX_COMPILER}
	-std=c++20 -Wall -Wextra 
	-x c++ -fsyntax-only
	${CMAKE_CURRENT_SOURCE_DIR}/skip_lists.hpp
	VERBATIM)

enable_testing()

add_executable(insert_get_tests tests/insert_get.cpp)
target_compile_features(insert_get_tests PRIVATE cxx_std_20)
target_compile_options(insert_get_tests PRIVATE -Wall -Wextra)
target_include_directories(insert_get_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

foreach(test_case IN ITEMS empty single missing insertion_orders many_keys)
	add_test(NAME insert_get_${test_case} COMMAND insert_get_tests ${test_case})
endforeach()
