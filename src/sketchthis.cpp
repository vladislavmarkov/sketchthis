#include <cstdlib>

#include "application.hpp"
#include "fps_ctl.hpp"
#include "sdl2.hpp"

int
main()
{
    sdl2::init();

    // create window
    sketchthis::application_t app("sketchthis");

    // fps controller
    misc::fps_ctl_t fps_ctl;

    // application loop
    while (app.is_running()) {
        app.handle_events();
        app.draw_frame();
        fps_ctl.update();
    }

    return EXIT_SUCCESS;
}
