#include "sdl2.hpp"

#include <cstdlib>
#include <stdexcept>

#include <SDL.h>

#include "window.hpp"

namespace sdl2 {

void
init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error(SDL_GetError());
    }
    std::atexit(SDL_Quit);
}

std::tuple<std::size_t, std::size_t, std::size_t, std::size_t>
get_widest_bounds()
{
    const auto display_num   = SDL_GetNumVideoDisplays();
    auto       widest_bounds = SDL_Rect{};
    for (auto display_no = 0; display_no != display_num; ++display_no) {
        SDL_Rect display_bounds;
        SDL_GetDisplayBounds(display_no, &display_bounds);
        if (display_bounds.w > widest_bounds.w) {
            widest_bounds = display_bounds;
        }
    }
    return std::forward_as_tuple(
        static_cast<std::size_t>(widest_bounds.x),
        static_cast<std::size_t>(widest_bounds.y),
        static_cast<std::size_t>(widest_bounds.w),
        static_cast<std::size_t>(widest_bounds.h));
}

void
warp_mouse(window_t* window, std::size_t x, std::size_t y)
{
    SDL_WarpMouseInWindow(*window, static_cast<int>(x), static_cast<int>(y));
}
}
