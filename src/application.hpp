#ifndef SKETCHTHIS_APPLICATION_HPP
#define SKETCHTHIS_APPLICATION_HPP

#include <memory>
#include <string_view>
#include <vector>

#include <boost/msm/back/state_machine.hpp>

#include "sdl2.hpp"

namespace sm {

struct _tlsm_t;
using tlsm_t = typename boost::msm::back::state_machine<_tlsm_t>;
} // namespace sm

struct SDL_Window;

namespace sdl2 {
class reactor_t;
class renderer_t;
class texture_t;
class window_t;
} // namespace sdl2

namespace sketchthis {

class application_t {
    std::size_t _pitch   = {0};
    bool        _running = {true};

private:
    std::unique_ptr<sdl2::window_t>   _window;
    std::unique_ptr<sdl2::renderer_t> _renderer;
    std::unique_ptr<sdl2::texture_t>  _texture;
    std::vector<uint8_t>              _data;
    std::unique_ptr<sm::tlsm_t>       _tlsm; // top-level state machine
    std::unique_ptr<sdl2::reactor_t>  _reactor;

public:
    application_t& operator=(const application_t&) = delete;
    application_t& operator=(application_t&&) = delete;
    application_t(const application_t&)       = delete;
    application_t(application_t&&)            = delete;

    application_t(std::string_view);
    ~application_t();

    int run();

    bool
    is_running() const
    {
        return _running;
    }

    void quit();

    sm::tlsm_t* tlsm();

    void set_reactor(std::unique_ptr<sdl2::reactor_t>&& reactor);

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

    std::vector<uint8_t>&
    data()
    {
        return _data;
    }
};
} // namespace sketchthis

#endif // SKETCHTHIS_APPLICATION_HPP
