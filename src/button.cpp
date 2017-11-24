#include "button.hpp"

#include "texture.hpp"

namespace sdl2 {

button_t::button_t(
    gsl::not_null<renderer_t*> renderer,
    const std::tuple<std::size_t, std::size_t, std::size_t, std::size_t>& rect)
    : _texture{std::make_unique<texture_t>(
          renderer, std::get<2>(rect), std::get<3>(rect))}
{
}

button_t::~button_t() = default;
}
