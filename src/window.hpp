#pragma once
#ifndef SDL2_WINDOW_HPP
#define SDL2_WINDOW_HPP

#include <cstdint>
#include <functional>
#include <memory>

struct SDL_Window;

namespace sdl2 {

class window_t {
    std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> _window;

public:
    window_t& operator=(const window_t&) = delete;
    window_t& operator=(window_t&&) = delete;
    window_t(const window_t&)       = delete;
    window_t(window_t&&)            = delete;

    window_t(
        const std::string& title,
        std::size_t        x,
        std::size_t        y,
        std::size_t        w,
        std::size_t        h);
    ~window_t();

    operator SDL_Window*();
};
}

#endif // SDL2_WINDOW_HPP
