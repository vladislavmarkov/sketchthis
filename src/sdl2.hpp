#pragma once
#ifndef SDL2_WRAPPER_HPP
#define SDL2_WRAPPER_HPP

#include <cstdint>
#include <tuple>

#include <gsl/gsl>

#include <SDL2/SDL_pixels.h>

namespace sdl2 {

using color_t = SDL_Color;

class window_t;

constexpr std::size_t pixel_size = {4}; // rgb + alpha = 4 bytes

void init();
void quit();

std::tuple<std::size_t, std::size_t, std::size_t, std::size_t>
get_widest_bounds();

void warp_mouse(
    gsl::not_null<window_t*>,
    const std::tuple<std::size_t, std::size_t>& point);
}

#endif // SDL2_WRAPPER_HPP
