cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(sketchthis)

file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.hpp)

add_definitions(
-std=gnu++1z
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

find_package(Boost 1.60 REQUIRED)
find_package(SDL2 REQUIRED)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
pkg_check_modules(SDL2_TTF SDL2_ttf>=2.0)

add_executable(sketchthis
	src/application.cpp
	src/application.hpp
	src/button.cpp
	src/button.hpp
	src/font.cpp
	src/font.hpp
	src/fps_ctl.cpp
	src/fps_ctl.hpp
	src/menu_reactor.cpp
	src/menu_reactor.hpp
	src/reactor.cpp
	src/reactor.hpp
	src/renderer.cpp
	src/renderer.hpp
	src/sdl2.cpp
	src/sdl2.hpp
	src/sdl2_ttf.cpp
	src/sdl2_ttf.hpp
	src/sketchthis.cpp
	src/surface.cpp
	src/surface.hpp
	src/texture.cpp
	src/texture.hpp
	src/tlsm.hpp
	src/tlsm_events.hpp
	src/window.cpp
	src/window.hpp
)

target_include_directories(sketchthis
PRIVATE
	${Boost_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
	${SDL2_TTF_INCLUDE_DIRS}
)

target_link_libraries(sketchthis
PRIVATE
	${Boost_LIBRARIES}
	${SDL2_LIBRARIES}
	${SDL2_TTF_LIBRARIES}
)

add_custom_target(clangformat
COMMAND
	/usr/bin/clang-format-3.8 -style=file -i ${ALL_SOURCE_FILES}
)
