#include <gsl/gsl>

#include "application.hpp"
#include "sdl2.hpp"
#include "sdl2_ttf.hpp"

// debug
#include <SDL.h>
#include <iostream>

int
main()
{
    sdl2::init();
    auto sdl2_quit = gsl::finally([]() { sdl2::quit(); });

    sdl2::ttf::init();
    auto sdl2_ttf_quit = gsl::finally([]() { sdl2::ttf::quit(); });

    std::cout << static_cast<uint16_t>(SDL_GetNumVideoDisplays()) << '\n';

    // run application
    return sketchthis::application_t("sketchthis").run();
}
