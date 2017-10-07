#include "window.hpp"

#include <SDL.h>

namespace sdl2 {

window_t::window_t(
    const std::string& title,
    std::size_t        x,
    std::size_t        y,
    std::size_t        w,
    std::size_t        h)
    : _window(
          SDL_CreateWindow(
              title.c_str(),
              static_cast<int>(x),
              static_cast<int>(y),
              static_cast<int>(w),
              static_cast<int>(h),
              SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN_DESKTOP |
                  SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_INPUT_GRABBED |
                  SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_SHOWN),
          [](SDL_Window* ptr) { SDL_DestroyWindow(ptr); })
{
    if (!_window) {
        throw std::runtime_error(SDL_GetError());
    }
}

window_t::~window_t() = default;

window_t::operator SDL_Window*() { return _window.get(); }
}
