#include "surface.hpp"

#include <SDL.h>

#include "term.hpp"

namespace sdl2 {

surface_t& surface_t::operator=(surface_t&&) = default;
surface_t::surface_t(surface_t&&)            = default;

surface_t::surface_t(gsl::not_null<SDL_Surface*> surface)
    : _surface(surface, [](SDL_Surface* ptr) {
          if (ptr) SDL_FreeSurface(ptr);
      })
{
    if (!_surface) TERM("failed to create surface");
}

surface_t::~surface_t() = default;

surface_t::operator SDL_Surface*() { return _surface.get(); }
} // namespace sdl2
