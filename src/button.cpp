#include "button.hpp"

#include "texture.hpp"

namespace sdl2 {

button_t::button_t(
    renderer_t* renderer,
    std::size_t x,
    std::size_t y,
    std::size_t w,
    std::size_t h)
    : _texture{std::make_unique<texture_t>(renderer, w, h)}
{
    (void)x;
    (void)y;
}

button_t::~button_t() = default;
}
