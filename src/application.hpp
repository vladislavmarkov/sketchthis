#pragma once
#ifndef SKETCHTHIS_APPLICATION_HPP
#define SKETCHTHIS_APPLICATION_HPP

#include <memory>
#include <string>
#include <vector>

#include <boost/msm/back/state_machine.hpp>

#include "reactor.hpp"

namespace sm {

struct _tlsm_t;
typedef boost::msm::back::state_machine<_tlsm_t> tlsm_t;
}

struct SDL_Window;

namespace sdl2 {
class renderer_t;
class texture_t;
}

namespace sketchthis {

class application_t {
    std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> _window;
    std::size_t _x = {0}, _y = {0}, _w = {0}, _h = {0};
    std::size_t _pitch   = {0};
    bool        _running = {true};

    std::unique_ptr<sdl2::renderer_t> _renderer;
    std::unique_ptr<sdl2::texture_t>  _texture;
    std::vector<std::uint8_t>         _data;
    std::unique_ptr<sm::tlsm_t>       _tlsm; // top-level state machine
    reactor_t                         _reactor;

public:
    application_t& operator=(const application_t&) = delete;
    application_t& operator=(application_t&&) = delete;
    application_t(const application_t&)       = delete;
    application_t(application_t&&)            = delete;

    application_t(const std::string& title);
    ~application_t();

    bool
    is_running() const
    {
        return _running;
    }

    void quit();

    sm::tlsm_t* tlsm();

    void handle_events();
    void draw_frame();

    void
    set_reactor(reactor_t&& reactor)
    {
        _reactor = std::move(reactor);
    }

    sdl2::renderer_t*
    renderer()
    {
        return _renderer.get();
    }

    sdl2::texture_t*
    texture()
    {
        return _texture.get();
    }

    std::size_t
    pitch() const
    {
        return _pitch;
    }

    std::vector<std::uint8_t>&
    data()
    {
        return _data;
    }
};
}

#endif // SKETCHTHIS_APPLICATION_HPP
