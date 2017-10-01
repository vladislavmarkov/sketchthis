#pragma once
#ifndef SDL2_TEXTURE_HPP
#define SDL2_TEXTURE_HPP

#include <cstdint>

#include <SDL.h>

namespace sdl2 {

class texture_t {
    SDL_Texture* _texture = {nullptr};

public:
    texture_t& operator=(const texture_t&) = delete;
    texture_t& operator=(texture_t&&) = delete;
    texture_t(const texture_t&)       = delete;
    texture_t(texture_t&&)            = delete;

    texture_t(SDL_Renderer* renderer, std::size_t width, std::size_t height);
    ~texture_t();

    operator SDL_Texture*() { return _texture; }
};
}

#endif // SDL2_TEXTURE_HPP
