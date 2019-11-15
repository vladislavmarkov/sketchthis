#include "sdl2.hpp"

#include <cstdlib>
#include <tuple>

#include <SDL.h>

#include "term.hpp"
#include "window.hpp"

namespace sdl2 {

void
init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) TERM(SDL_GetError());
}

void
quit()
{
    SDL_Quit();
}

rect_t
get_widest_bounds()
{
    const auto display_num = SDL_GetNumVideoDisplays();
    auto       wb          = SDL_Rect{};
    for (auto display_no = 0; display_no != display_num; ++display_no) {
        SDL_Rect display_bounds;
        if (0 > SDL_GetDisplayUsableBounds(display_no, &display_bounds)) {
            TERM(SDL_GetError());
        }

        if (display_bounds.w > wb.w) { wb = display_bounds; }
    }
    return wb;
}

void
warp_mouse(gsl::not_null<window_t*> window, const point_t& point)
{
    SDL_WarpMouseInWindow(*window, point.x, point.y);
}
} // namespace sdl2
