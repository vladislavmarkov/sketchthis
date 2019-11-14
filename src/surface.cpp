#include "surface.hpp"

#include <iostream>

#include <SDL.h>

namespace sdl2 {

surface_t& surface_t::operator=(surface_t&&) = default;
surface_t::surface_t(surface_t&&)            = default;

surface_t::surface_t(SDL_Surface* surface)
    : _surface(surface, [](SDL_Surface* ptr) {
          if (ptr) SDL_FreeSurface(ptr);
      })
{
    if (!_surface) { std::cerr << "can't construct surface_t from nullptr\n"; }
}

surface_t::~surface_t() = default;

surface_t::operator SDL_Surface*() { return _surface.get(); }
} // namespace sdl2
