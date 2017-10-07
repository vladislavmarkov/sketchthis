#include "texture.hpp"

#include <stdexcept>

#include <SDL.h>

#include "renderer.hpp"

namespace sdl2 {

namespace {

void
destroy_texture(SDL_Texture* ptr)
{
    if (ptr) SDL_DestroyTexture(ptr);
}
}

texture_t::texture_t(
    renderer_t* renderer, std::size_t width, std::size_t height)
    : _texture(
          SDL_CreateTexture(
              *renderer,
              SDL_PIXELFORMAT_ARGB8888,
              SDL_TEXTUREACCESS_STREAMING,
              static_cast<int>(width),
              static_cast<int>(height)),
          destroy_texture)
{
    if (!_texture) {
        throw std::runtime_error(SDL_GetError());
    }
}

texture_t::texture_t(SDL_Texture* texture) : _texture(texture, destroy_texture)
{
    if (!_texture) {
        throw std::invalid_argument("can't construct texture_t from nullptr");
    }
}

texture_t::~texture_t() = default;

texture_t::operator SDL_Texture*() { return _texture.get(); }
std::tuple<std::size_t, std::size_t>
texture_t::get_bounds() const
{
    int w, h;
    if (SDL_QueryTexture(
            const_cast<SDL_Texture*>(_texture.get()),
            nullptr,
            nullptr,
            &w,
            &h)) {
        throw std::runtime_error("failed to get texture bounds");
    }
    return std::forward_as_tuple(
        static_cast<std::size_t>(w), static_cast<std::size_t>(h));
}
}
