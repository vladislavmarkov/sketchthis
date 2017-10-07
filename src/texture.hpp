#pragma once
#ifndef SDL2_TEXTURE_HPP
#define SDL2_TEXTURE_HPP

#include <cstdint>
#include <functional>
#include <memory>
#include <tuple>

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

    texture_t(renderer_t*, std::size_t width, std::size_t height);
    texture_t(SDL_Texture*);
    ~texture_t();

    operator SDL_Texture*();

    std::tuple<std::size_t, std::size_t> get_bounds() const;
};
}

#endif // SDL2_TEXTURE_HPP
