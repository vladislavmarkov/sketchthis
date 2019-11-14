#include "sdl2.hpp"

#include <cstdlib>
#include <iostream>
#include <tuple>

#include <SDL.h>

#include "window.hpp"

namespace sdl2 {

void
init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << SDL_GetError() << '\n';
        std::terminate();
    }
}

void
quit()
{
    SDL_Quit();
}

void
warp_mouse(gsl::not_null<window_t*> window, const point_t& point)
{
    SDL_WarpMouseInWindow(*window, point.x, point.y);
}
} // namespace sdl2
