#include "texture.hpp"

#include <SDL.h>

#include "renderer.hpp"
#include "term.hpp"

namespace sdl2 {

namespace {

void
destroy_texture(gsl::not_null<SDL_Texture*> ptr)
{
    SDL_DestroyTexture(ptr);
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
    if (!_texture) TERM(SDL_GetError());
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
            const_cast<SDL_Texture*>(_texture.get()), nullptr, nullptr, &w, &h))
        TERM("failed to get texture bounds");

    return {w, h};
}
} // namespace sdl2
