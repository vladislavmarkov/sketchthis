#include <cstdlib>
#include <cstring>
#include <memory>

#include <SDL.h>

#include "fps_ctl.hpp"
#include "sdl2_helpers.hpp"

int
main()
{
    sdl2::init();

    // create window
    sdl2::window_t window("sketchthis");

    // make frame buffer
    constexpr std::size_t pixel_size = {4}; // rgb + alpha = 4 bytes
    const auto            area       = window.get_width() * window.get_height();
    const auto            buffer_length = area * pixel_size;
    auto       data  = std::make_unique<std::uint8_t[]>(buffer_length);
    const auto pitch = static_cast<int>(window.get_width() * pixel_size);
    std::memset(data.get(), 0, buffer_length);

    // create renderer
    sdl2::renderer_t renderer(window);

    // create texture
    sdl2::texture_t texture(renderer, window);

    misc::fps_ctl_t fps_ctl;
    auto            done = false;
    SDL_Event       event;

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
        SDL_UpdateTexture(texture, nullptr, data.get(), pitch);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
        fps_ctl.update();
    }

    return EXIT_SUCCESS;
}
