#include "sdl2.hpp"

#include <cstdlib>
#include <stdexcept>

#include <gsl/gsl>

#include <SDL.h>

#include "window.hpp"

namespace sdl2 {

void
init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error(SDL_GetError());
    }
}

void
quit()
{
    SDL_Quit();
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
        gsl::narrow<std::size_t>(widest_bounds.x),
        gsl::narrow<std::size_t>(widest_bounds.y),
        gsl::narrow<std::size_t>(widest_bounds.w),
        gsl::narrow<std::size_t>(widest_bounds.h));
}

void
warp_mouse(
    gsl::not_null<window_t*> window,
    const std::tuple<std::size_t, std::size_t>& point)
{
    SDL_WarpMouseInWindow(
        *window,
        gsl::narrow<int>(std::get<0>(point)),
        gsl::narrow<int>(std::get<1>(point)));
}
}
