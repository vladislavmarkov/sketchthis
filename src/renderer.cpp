#include "renderer.hpp"

#include <SDL.h>

#include "term.hpp"
#include "window.hpp"

namespace sdl2 {

renderer_t::renderer_t(gsl::not_null<window_t*> window)
    : _renderer(
          SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED),
          [](SDL_Renderer* ptr) { SDL_DestroyRenderer(ptr); })
{
    if (!_renderer) TERM("failed to create renderer");
}

renderer_t::~renderer_t() = default;

renderer_t::operator SDL_Renderer*() { return _renderer.get(); }
} // namespace sdl2
