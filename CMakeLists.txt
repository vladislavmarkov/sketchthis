cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(sketchthis)

file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.hpp)

add_definitions(
-std=gnu++14
-Wall
-Werror
-Wextra
-pedantic
-Wconversion
-Winit-self
-Woverloaded-virtual
-Wunreachable-code
-Wold-style-cast
-Wsign-promo
-Wshadow
)

include(FindPkgConfig)

find_package(SDL2 REQUIRED)

add_executable(sketchthis
	src/sketchthis.cpp
)

target_include_directories(sketchthis
PRIVATE
	${SDL2_INCLUDE_DIRS}
)

target_link_libraries(sketchthis
PRIVATE
	${SDL2_LIBRARIES}
)

add_custom_target(clangformat
COMMAND
	/usr/bin/clang-format-3.8 -style=file -i ${ALL_SOURCE_FILES}
)
