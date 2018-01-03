cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(sketchthis)

include(CMakePackageConfigHelpers)
include(FindPkgConfig)
include(GNUInstallDirs)

set(CMAKE_USE_RELATIVE_PATHS TRUE)
set(INSTALL_INCLUDE_DIR "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}-${PROJECT_VERSION}")
set(INSTALL_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake")
set(INSTALL_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake")

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

find_package(Boost 1.65 REQUIRED)
pkg_check_modules(SDL2 sdl2>=2.0.5 REQUIRED)
pkg_check_modules(SDL2_TTF SDL2_ttf>=2.0 REQUIRED)


set(SKETCHTHIS_SOURCES
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
src/window.hpp)

# setting up a format command
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
	add_custom_target(
		format
	COMMAND
		clang-format -style=file -i ${SKETCHTHIS_SOURCES}
	WORKING_DIRECTORY
		${CMAKE_SOURCE_DIR})
endif()

# setting up a lint command
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
	add_custom_target(
		lint
	COMMAND
		clang-tidy
		${SKETCHTHIS_SOURCES}
		--
		-std=gnu++1z
	WORKING_DIRECTORY
		${CMAKE_SOURCE_DIR})
endif()

add_executable(sketchthis ${SKETCHTHIS_SOURCES})

target_include_directories(sketchthis
PRIVATE
	${Boost_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
	${SDL2_TTF_INCLUDE_DIRS}
)

target_link_libraries(sketchthis
PRIVATE
	stdc++fs
	${Boost_LIBRARIES}
	${SDL2_LIBRARIES}
	${SDL2_TTF_LIBRARIES}
)

install(TARGETS sketchthis
EXPORT
	"${PROJECT_NAME}"
RUNTIME DESTINATION
	"${CMAKE_INSTALL_BINDIR}"
COMPONENT
	Runtime
)
