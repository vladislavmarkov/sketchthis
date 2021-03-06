#ifndef SDL2_WINDOW_HPP
#define SDL2_WINDOW_HPP

#include <cstdint>
#include <functional>
#include <memory>
#include <string_view>
#include <tuple>

#include "sdl2.hpp"

struct SDL_Window;

namespace sdl2 {

class window_t {
    std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> _window;

public:
    window_t& operator=(const window_t&) = delete;
    window_t& operator=(window_t&&) = delete;
    window_t(const window_t&)       = delete;
    window_t(window_t&&)            = delete;

    window_t(std::string_view, const sdl2::rect_t&);
    ~window_t();

    operator SDL_Window*();
};
} // namespace sdl2

#endif // SDL2_WINDOW_HPP
