#include "application.hpp"

#include <tuple>

#include <SDL.h>

#include "fps_ctl.hpp"
#include "reactor.hpp"
#include "renderer.hpp"
#include "sdl2.hpp"
#include "texture.hpp"
#include "tlsm.hpp"
#include "window.hpp"

namespace sketchthis {

application_t::application_t(std::string_view title)
{
    const auto [x, y, w, h] = sdl2::get_widest_bounds();

    _pitch  = w * sdl2::pixel_size;
    _data   = std::vector<uint8_t>(w * h * sdl2::pixel_size, 0);
    _window = std::make_unique<sdl2::window_t>(title, sdl2::rect_t{x, y, w, h});
    _renderer = std::make_unique<sdl2::renderer_t>(_window.get());
    _texture =
        std::make_unique<sdl2::texture_t>(_renderer.get(), sdl2::area_t{w, h});

    sdl2::warp_mouse(_window.get(), sdl2::point_t{w / 2, h / 2});

    // create state machine
    _tlsm = std::make_unique<sm::tlsm_t>();

    // associate state machine with application
    _tlsm->set_app_ptr(this);
    _tlsm->start();
}

application_t::~application_t() = default;

int
application_t::run()
{
    // fps controller
    fps_ctl_t fps_ctl;

    // application loop
    while (is_running()) {
        handle_events(_reactor.get());
        _reactor->on_draw_frame();
        fps_ctl.update();
    }

    return EXIT_SUCCESS;
}

void
application_t::quit()
{
    _running = false;
}

sm::tlsm_t*
application_t::tlsm()
{
    return _tlsm.get();
}

void
application_t::set_reactor(std::unique_ptr<sdl2::reactor_t>&& reactor)
{
    _reactor = std::move(reactor);
}
} // namespace sketchthis
