#include "texture.hpp"

#include <iostream>

#include <SDL.h>

#include "renderer.hpp"

namespace sdl2 {

namespace {

void
destroy_texture(SDL_Texture* ptr)
{
    if (ptr) SDL_DestroyTexture(ptr);
}
} // namespace

texture_t::texture_t(gsl::not_null<renderer_t*> renderer, const area_t& area)
    : _texture(
          SDL_CreateTexture(
              *renderer,
              SDL_PIXELFORMAT_ARGB8888,
              SDL_TEXTUREACCESS_STREAMING,
              area[0],
              area[1]),
          destroy_texture)
{
    if (!_texture) {
        std::cerr << SDL_GetError() << '\n';
        std::terminate();
    }
}

texture_t::texture_t(gsl::not_null<SDL_Texture*> texture)
    : _texture(texture, destroy_texture)
{
}

texture_t::~texture_t() = default;

texture_t::operator SDL_Texture*() { return _texture.get(); }

area_t
texture_t::get_area() const
{
    int w, h;
    if (SDL_QueryTexture(
            const_cast<SDL_Texture*>(_texture.get()),
            nullptr,
            nullptr,
            &w,
            &h)) {
        std::cerr << "failed to get texture bounds\n";
    }
    return {w, h};
}
} // namespace sdl2
