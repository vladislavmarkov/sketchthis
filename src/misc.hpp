#pragma once
#ifndef SDL_MISC_HPP
#define SDL_MISC_HPP

#include <tuple>

namespace sdl2 {

std::tuple<std::size_t, std::size_t, std::size_t, std::size_t>
get_widest_bounds();
}

#endif // SDL_MISC_HPP