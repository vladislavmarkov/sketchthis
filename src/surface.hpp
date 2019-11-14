#ifndef SDL2_SURFACE_HPP
#define SDL2_SURFACE_HPP

#include <functional>
#include <memory>

struct SDL_Surface;

namespace sdl2 {

class surface_t {
    std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface*)>> _surface;

public:
    surface_t& operator=(const surface_t&) = delete;
    surface_t& operator                    =(surface_t&&);
    surface_t(const surface_t&)            = delete;
    surface_t(surface_t&&);

    surface_t(SDL_Surface* surface);
    ~surface_t();

    operator SDL_Surface*();
};
} // namespace sdl2

#endif // SDL2_SURFACE_HPP
