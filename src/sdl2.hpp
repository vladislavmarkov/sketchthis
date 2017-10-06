#pragma once
#ifndef SDL2_WRAPPER_HPP
#define SDL2_WRAPPER_HPP

#include <cstdint>
#include <tuple>

namespace sdl2 {

constexpr std::size_t pixel_size = {4}; // rgb + alpha = 4 bytes

void init();

std::tuple<std::size_t, std::size_t, std::size_t, std::size_t>
get_widest_bounds();
}

#endif // SDL2_WRAPPER_HPP
