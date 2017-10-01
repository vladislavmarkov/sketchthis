#include "sdl2.hpp"

#include <stdexcept>

#include <SDL.h>

namespace sdl2 {

void
init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error(SDL_GetError());
    }
    std::atexit([]() { SDL_Quit(); });
}
}
