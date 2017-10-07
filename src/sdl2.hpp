#pragma once
#ifndef SDL2_WRAPPER_HPP
#define SDL2_WRAPPER_HPP

#include <cstdint>
#include <tuple>

#include <SDL2/SDL_pixels.h>

namespace sdl2 {

using color_t = SDL_Color;

class window_t;

constexpr std::size_t pixel_size = {4}; // rgb + alpha = 4 bytes

void init();

std::tuple<std::size_t, std::size_t, std::size_t, std::size_t>
get_widest_bounds();

void warp_mouse(window_t*, std::size_t x, std::size_t y);
}

#endif // SDL2_WRAPPER_HPP
