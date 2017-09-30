#include <cstdlib>
#include <cstring>
#include <memory>

#include <SDL.h>

#include "fps_counter.hpp"
#include "sdl_rm.hpp"

using namespace sdl2_helpers;

namespace {

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
}

int
main()
{
    // initialize sdl2
    sdl2_rm_t sdl2;
    (void)sdl2;

    // get the widest display (assume, user'd want to make a sketch on it)
    const auto display_bounds = get_widest_bounds();

    // make frame buffer
    constexpr auto pixel_size    = 4; // rgb + alpha = 4 bytes
    const auto     buffer_length = static_cast<std::size_t>(
        display_bounds.w * display_bounds.h * pixel_size);
    auto       data  = std::make_unique<std::uint8_t[]>(buffer_length);
    const auto pitch = display_bounds.w * pixel_size;
    std::memset(data.get(), 0x00, buffer_length);

    // create window
    win_rm_t win_rm("sketchthis", display_bounds);
    (void)win_rm;

    // create renderer
    renderer_rm_t renderer_rm(win_rm.window);
    (void)renderer_rm;

    // create texture
    texture_rm_t texture_rm(renderer_rm.renderer, display_bounds);
    (void)texture_rm;

    misc::fps_counter_t fps_counter;

    auto      done = false;
    SDL_Event event;

    while (!done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: done    = true; break;
            case SDL_KEYDOWN: done = event.key.keysym.sym == SDLK_ESCAPE; break;
            case SDL_MOUSEMOTION:
                std::memset(
                    &data[pitch * event.motion.y + event.motion.x * pixel_size],
                    0xff,
                    pixel_size);
                break;
            default: break;
            }
        }
        SDL_UpdateTexture(texture_rm.texture, nullptr, data.get(), pitch);
        SDL_RenderCopy(
            renderer_rm.renderer, texture_rm.texture, nullptr, nullptr);
        SDL_RenderPresent(renderer_rm.renderer);
        fps_counter.update();
    }

    return EXIT_SUCCESS;
}
