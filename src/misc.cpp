#include "misc.hpp"

#include <SDL.h>

namespace sdl2 {

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
}
