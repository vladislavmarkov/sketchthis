#include "renderer.hpp"

namespace sdl2 {

renderer_t::renderer_t(SDL_Window* window)
    : _renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED))
{
}

renderer_t::~renderer_t()
{
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
    }
}
}
