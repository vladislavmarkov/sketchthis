#include "menu_reactor.hpp"

#include <cassert>

#include <SDL.h>

#include "application.hpp"
#include "tlsm.hpp"

namespace sketchthis {

reactor_t
menu_reactor(application_t* app)
{
    assert(app);

    return reactor_t(
        [app](int keysym) {
            switch (keysym) {
            case SDLK_ESCAPE: app->quit(); break;
            case SDLK_n: app->tlsm()->process_event(sm::new_canvas()); break;
            case SDLK_d:
                app->tlsm()->process_event(sm::discard_canvas());
                break;
            default: break;
            }
        },
        [](std::size_t, std::size_t) {},
        [app]() { app->quit(); });
}
}
