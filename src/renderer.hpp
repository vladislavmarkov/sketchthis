#pragma once
#ifndef SDL2_RENDERER_HPP
#define SDL2_RENDERER_HPP

#include <SDL.h>

namespace sdl2 {

class renderer_t {
    SDL_Renderer* _renderer = {nullptr};

public:
    renderer_t& operator=(const renderer_t&) = delete;
    renderer_t& operator=(renderer_t&&) = delete;
    renderer_t(const renderer_t&)       = delete;
    renderer_t(renderer_t&&)            = delete;

    renderer_t(SDL_Window* window);
    ~renderer_t();

    operator SDL_Renderer*() { return _renderer; }
};
}

#endif // SDL2_RENDERER_HPP
