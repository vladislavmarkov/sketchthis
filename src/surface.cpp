#include "surface.hpp"

#include <stdexcept>

#include <SDL.h>

namespace sdl2 {

surface_t& surface_t::operator=(surface_t&&) = default;
surface_t::surface_t(surface_t&&)            = default;

surface_t::surface_t(SDL_Surface* surface)
    : _surface(surface, [](SDL_Surface* ptr) {
          if (ptr) SDL_FreeSurface(ptr);
      })
{
    if (!_surface) {
        throw std::invalid_argument("can't construct surface_t from nullptr");
    }
}

surface_t::~surface_t() = default;

surface_t::operator SDL_Surface*() { return _surface.get(); }
}
