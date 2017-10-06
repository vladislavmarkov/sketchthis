#include "sdl2.hpp"

#include <cassert>
#include <cstdlib>
#include <stdexcept>

#include <SDL.h>
#include <SDL_ttf.h>

namespace sdl2 {

void
init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error(SDL_GetError());
    }
    std::atexit(SDL_Quit);

    if (TTF_Init() < 0) {
        throw std::runtime_error(TTF_GetError());
    }
    std::atexit(TTF_Quit);

    const SDL_version* linked_version = TTF_Linked_Version();
    SDL_version        compiled_version;
    SDL_TTF_VERSION(&compiled_version);

    assert(linked_version->major == compiled_version.major);
    assert(linked_version->minor == compiled_version.minor);
    assert(linked_version->patch == compiled_version.patch);
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
}
