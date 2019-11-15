#include "window.hpp"

#include "term.hpp"

#include <SDL.h>

namespace sdl2 {

window_t::window_t(std::string_view title, const rect_t& rect)
    : _window(
          SDL_CreateWindow(
              title.data(),
              rect.x,
              rect.y,
              rect.w,
              rect.h,
              SDL_WINDOW_MAXIMIZED | SDL_WINDOW_BORDERLESS | SDL_WINDOW_OPENGL |
                  SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS |
                  SDL_WINDOW_SHOWN),
          [](SDL_Window* ptr) { SDL_DestroyWindow(ptr); })
{
    if (!_window) TERM(SDL_GetError());
}

window_t::~window_t() = default;

window_t::operator SDL_Window*() { return _window.get(); }
} // namespace sdl2
