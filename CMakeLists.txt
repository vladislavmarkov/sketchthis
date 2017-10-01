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
-DBOOST_LOG_DYN_LINK
)

include(FindPkgConfig)

find_package(SDL2 REQUIRED)
find_package(Boost 1.60 REQUIRED log)

add_executable(sketchthis
	src/application.cpp
	src/application.hpp
	src/fps_ctl.cpp
	src/fps_ctl.hpp
	src/menu_reactor.cpp
	src/menu_reactor.hpp
	src/misc.cpp
	src/misc.hpp
	src/reactor.hpp
	src/renderer.cpp
	src/renderer.hpp
	src/sdl2.cpp
	src/sdl2.hpp
	src/sketchthis.cpp
	src/texture.cpp
	src/texture.hpp
	src/tlsm.hpp
	src/tlsm_events.hpp
)

target_include_directories(sketchthis
PRIVATE
	${Boost_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
)

target_link_libraries(sketchthis
PRIVATE
	${Boost_LIBRARIES}
	${SDL2_LIBRARIES}
)

add_custom_target(clangformat
COMMAND
	/usr/bin/clang-format-3.8 -style=file -i ${ALL_SOURCE_FILES}
)
