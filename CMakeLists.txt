cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(sketchthis VERSION 0.1.0 LANGUAGES CXX)

include(CMakePackageConfigHelpers)
include(FindPkgConfig)
include(FindPkgConfig)
include(GNUInstallDirs)

find_package(Boost 1.65 REQUIRED)
pkg_check_modules(SDL2 sdl2>=2.0.10 REQUIRED)
pkg_check_modules(SDL2_TTF SDL2_ttf>=2.0 REQUIRED)

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
    src/term.hpp
    src/texture.cpp
    src/texture.hpp
    src/tlsm.hpp
    src/tlsm_events.hpp
    src/window.cpp
    src/window.hpp)

set_source_files_properties(
    src/font.cpp
    src/menu_reactor.cpp
PROPERTIES
COMPILE_OPTIONS
    -fexceptions)

target_compile_features(sketchthis
PRIVATE
    cxx_std_17)

target_compile_options(sketchthis
PRIVATE
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
    -fno-exceptions)

target_include_directories(sketchthis
PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS})

target_link_libraries(sketchthis
PRIVATE
    stdc++fs
    ${SDL2_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${Boost_LIBRARIES})
