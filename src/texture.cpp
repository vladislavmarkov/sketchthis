#include "texture.hpp"

#include <stdexcept>

namespace sdl2 {

texture_t::texture_t(
    SDL_Renderer* renderer, std::size_t width, std::size_t height)
    : _texture(
          SDL_CreateTexture(
              renderer,
              SDL_PIXELFORMAT_ARGB8888,
              SDL_TEXTUREACCESS_STREAMING,
              static_cast<int>(width),
              static_cast<int>(height)))
{
    if (!_texture) {
        throw std::runtime_error(SDL_GetError());
    }
}

texture_t::~texture_t()
{
    if (_texture) {
        SDL_DestroyTexture(_texture);
    }
}
}
