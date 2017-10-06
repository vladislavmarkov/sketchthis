#include "renderer.hpp"

#include <SDL.h>

namespace sdl2 {

renderer_t::renderer_t(SDL_Window* window)
    : _renderer(
          SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED),
          [](SDL_Renderer* ptr) { SDL_DestroyRenderer(ptr); })
{
    if (!_renderer) {
        throw std::runtime_error("failed to create renderer");
    }
}

renderer_t::~renderer_t() = default;

renderer_t::operator SDL_Renderer*() { return _renderer.get(); }
}
