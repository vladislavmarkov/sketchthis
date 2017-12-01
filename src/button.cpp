#include "button.hpp"

#include "texture.hpp"

namespace sdl2 {

button_t::button_t(gsl::not_null<renderer_t*> renderer, const rect_t& rect)
    : _texture{std::make_unique<texture_t>(renderer, area_t{rect.w, rect.h})}
{
}

button_t::~button_t() = default;
}
