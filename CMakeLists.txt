cmake_minimum_required(VERSION 3.16)

project(SkipLists LANGUAGES CXX)

add_custom_target(check_header
	COMMAND ${CMAKE_CXX_COMPILER}
	-std=c++20 -Wall -Wextra 
	-x c++ -fsyntax-only
	${CMAKE_CURRENT_SOURCE_DIR}/skip_lists.hpp
	VERBATIM)
