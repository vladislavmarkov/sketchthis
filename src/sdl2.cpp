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
}

void
quit()
{
    SDL_Quit();
}

rect_t
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
    return widest_bounds;
}

void
warp_mouse(gsl::not_null<window_t*> window, const point_t& point)
{
    SDL_WarpMouseInWindow(*window, point.x, point.y);
}
}
