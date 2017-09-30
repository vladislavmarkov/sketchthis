#include <chrono>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <thread>

#include <SDL.h>

#include "at_scope_exit.hpp"

using namespace std::chrono_literals;
using nonstd::at_scope_exit;

int
main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error(SDL_GetError());
    }
    auto sdl_cleanup = at_scope_exit<void()>([]() { SDL_Quit(); });

    SDL_DisplayMode display_mode;
    int             request = SDL_GetDesktopDisplayMode(1, &display_mode);
    if (request != 0) {
        throw std::runtime_error(SDL_GetError());
    }
    const std::size_t buffer_length = {
        static_cast<std::size_t>(display_mode.w * display_mode.h * 4)};
    std::unique_ptr<std::uint8_t[]> data =
        std::make_unique<std::uint8_t[]>(buffer_length);
    const auto pitch = display_mode.w * 4;
    std::memset(data.get(), 0x00, buffer_length);

    SDL_Rect display_bounds;
    SDL_GetDisplayBounds(1, &display_bounds);

    auto window = SDL_CreateWindow(
        "sketchthis",
        display_bounds.x,
        display_bounds.y,
        display_bounds.w,
        display_bounds.h,
        SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN_DESKTOP |
            SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_INPUT_GRABBED |
            SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_SHOWN);
    if (!window) {
        throw std::runtime_error(SDL_GetError());
    }
    auto window_cleanup = at_scope_exit<void()>([&window]() {
        if (window) {
            SDL_DestroyWindow(window);
        }
    });

    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        throw std::runtime_error(SDL_GetError());
    }
    auto renderer_cleanup = at_scope_exit<void()>([&renderer]() {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
    });

    auto target_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        display_mode.w,
        display_mode.h);
    if (!target_texture) {
        throw std::runtime_error(SDL_GetError());
    }
    auto texture_cleanup = at_scope_exit<void()>([&target_texture]() {
        if (target_texture) {
            SDL_DestroyTexture(target_texture);
        }
    });

    auto      done = false;
    SDL_Event event;

    while (!done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: done    = true; break;
            case SDL_KEYDOWN: done = event.key.keysym.sym == SDLK_ESCAPE; break;
            case SDL_MOUSEMOTION:
                std::memset(
                    &data[pitch * event.motion.y + event.motion.x * 4],
                    0xff,
                    4);
                break;
            default: break;
            }
        }
        SDL_UpdateTexture(target_texture, nullptr, data.get(), pitch);
        SDL_RenderCopy(renderer, target_texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
        std::this_thread::sleep_for(50ms);
    }

    return EXIT_SUCCESS;
}
