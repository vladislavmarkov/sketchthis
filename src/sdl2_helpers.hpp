#pragma once
#ifndef SDL2_HELPERS_HPP
#define SDL2_HELPERS_HPP

#include <stdexcept>

#include <SDL.h>

namespace sdl2 {

SDL_Rect
get_widest_bounds()
{
    const auto display_num   = SDL_GetNumVideoDisplays();
    auto       widest_bounds = SDL_Rect{};
    for (auto display_no = 0; display_no != display_num; ++display_no) {
        SDL_Rect display_bounds;
        SDL_GetDisplayBounds(display_no, &display_bounds);
        if (display_bounds.w > widest_bounds.w) {
            widest_bounds = display_bounds;
        }
    }
    return widest_bounds;
}

void
init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error(SDL_GetError());
    }
    std::atexit([]() { SDL_Quit(); });
}

class window_t {
    SDL_Window* _window = {nullptr};
    SDL_Rect    _bounds = {};

public:
    window_t& operator=(const window_t&) = delete;
    window_t& operator=(window_t&&) = delete;
    window_t(const window_t&)       = delete;
    window_t(window_t&&)            = delete;

    window_t(const std::string& title) : _bounds(get_widest_bounds())
    {
        _window = SDL_CreateWindow(
            title.c_str(),
            _bounds.x,
            _bounds.y,
            _bounds.w,
            _bounds.h,
            SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN_DESKTOP |
                SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_INPUT_GRABBED |
                SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_SHOWN);

        if (!_window) {
            throw std::runtime_error(SDL_GetError());
        }

        SDL_WarpMouseInWindow(_window, _bounds.w / 2, _bounds.h / 2);
    }

    ~window_t()
    {
        if (_window) {
            SDL_DestroyWindow(_window);
        }
    }

    std::size_t
    get_width() const
    {
        return _bounds.w;
    }

    std::size_t
    get_height() const
    {
        return _bounds.h;
    }

    operator SDL_Window*() { return _window; }
};

class renderer_t {
    SDL_Renderer* _renderer = {nullptr};

public:
    renderer_t& operator=(const renderer_t&) = delete;
    renderer_t& operator=(renderer_t&&) = delete;
    renderer_t(const renderer_t&)       = delete;
    renderer_t(renderer_t&&)            = delete;

    renderer_t(window_t& window)
        : _renderer(
              SDL_CreateRenderer(
                  static_cast<SDL_Window*>(window),
                  -1,
                  SDL_RENDERER_ACCELERATED))
    {
    }

    ~renderer_t()
    {
        if (_renderer) {
            SDL_DestroyRenderer(_renderer);
        }
    }

    operator SDL_Renderer*() { return _renderer; }
};

class texture_t {
    SDL_Texture* _texture = {nullptr};

public:
    texture_t& operator=(const texture_t&) = delete;
    texture_t& operator=(texture_t&&) = delete;
    texture_t(const texture_t&)       = delete;
    texture_t(texture_t&&)            = delete;

    texture_t(renderer_t& renderer, const window_t& window)
        : _texture(
              SDL_CreateTexture(
                  static_cast<SDL_Renderer*>(renderer),
                  SDL_PIXELFORMAT_ARGB8888,
                  SDL_TEXTUREACCESS_STREAMING,
                  static_cast<int>(window.get_width()),
                  static_cast<int>(window.get_height())))
    {
        if (!_texture) {
            throw std::runtime_error(SDL_GetError());
        }
    }

    ~texture_t()
    {
        if (_texture) {
            SDL_DestroyTexture(_texture);
        }
    }

    operator SDL_Texture*() { return _texture; }
};
}

#endif // SDL2_HELPERS_HPP
