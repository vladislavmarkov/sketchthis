#ifndef SDL2_RENDERER_HPP
#define SDL2_RENDERER_HPP

#include <functional>
#include <gsl/pointers>
#include <memory>

struct SDL_Renderer;

namespace sdl2 {

class window_t;

class renderer_t {
    std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>> _renderer;

public:
    renderer_t& operator=(const renderer_t&) = delete;
    renderer_t& operator=(renderer_t&&) = delete;
    renderer_t(const renderer_t&)       = delete;
    renderer_t(renderer_t&&)            = delete;

    renderer_t(gsl::not_null<window_t*> window);
    ~renderer_t();

    operator SDL_Renderer*();
};
} // namespace sdl2

#endif // SDL2_RENDERER_HPP
