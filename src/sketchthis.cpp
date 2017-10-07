#include "application.hpp"
#include "sdl2.hpp"
#include "sdl2_ttf.hpp"

int
main()
{
    sdl2::init();
    sdl2::ttf::init();

    // run application
    return sketchthis::application_t("sketchthis").run();
}
