#include "reactor.hpp"

#include <SDL.h>

namespace sdl2 {

void
handle_events(gsl::not_null<reactor_t*> reactor)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            if (reactor) {
                reactor->on_quit();
            }
            break;
        case SDL_KEYDOWN:
            if (reactor) {
                reactor->on_keydown(event.key.keysym.sym);
            }
            break;
        case SDL_MOUSEMOTION:
            if (reactor) {
                reactor->on_mouse_move({event.motion.x, event.motion.y});
            }
            break;
        default: break;
        }
    }
}
}
