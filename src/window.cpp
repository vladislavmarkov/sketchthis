#include "window.hpp"

#include <iostream>

#include <SDL.h>

namespace sdl2 {

window_t::window_t(std::string_view title, const area_t& area)
    : _window(
          SDL_CreateWindow(
              title.data(),
              SDL_WINDOWPOS_UNDEFINED,
              SDL_WINDOWPOS_UNDEFINED,
              area[0],
              area[1],
              SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL |
                  SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_INPUT_GRABBED |
                  SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_SHOWN),
          [](SDL_Window* ptr) { SDL_DestroyWindow(ptr); })
{
    if (!_window) {
        std::cerr << SDL_GetError() << '\n';
        std::terminate();
    }
}

window_t::~window_t() = default;

window_t::operator SDL_Window*() { return _window.get(); }
} // namespace sdl2
