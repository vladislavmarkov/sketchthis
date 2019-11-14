#ifndef SDL2_TEXTURE_HPP
#define SDL2_TEXTURE_HPP

#include <cstdint>
#include <functional>
#include <memory>
#include <tuple>

#include <gsl/gsl>

#include "sdl2.hpp"

struct SDL_Texture;

namespace sdl2 {

class renderer_t;

class texture_t {
    std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture*)>> _texture;

public:
    texture_t& operator=(const texture_t&) = delete;
    texture_t& operator=(texture_t&&) = delete;
    texture_t(const texture_t&)       = delete;
    texture_t(texture_t&&)            = delete;

    texture_t(gsl::not_null<renderer_t*>, const area_t&);
    texture_t(gsl::not_null<SDL_Texture*>);
    ~texture_t();

    operator SDL_Texture*();

    area_t get_area() const;
};
} // namespace sdl2

#endif // SDL2_TEXTURE_HPP
