#include "window.hpp"

#include <SDL.h>

namespace sdl2 {

window_t::window_t(
    std::string_view title,
    const std::tuple<std::size_t, std::size_t, std::size_t, std::size_t>& rect)
    : _window(
          SDL_CreateWindow(
              title.data(),
              static_cast<int>(std::get<0>(rect)),
              static_cast<int>(std::get<1>(rect)),
              static_cast<int>(std::get<2>(rect)),
              static_cast<int>(std::get<3>(rect)),
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
