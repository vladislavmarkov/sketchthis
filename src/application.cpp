#include "application.hpp"

#include <cstring>

#include "misc.hpp"
#include "renderer.hpp"
#include "sdl2.hpp"
#include "texture.hpp"
#include "tlsm.hpp"

namespace sketchthis {

application_t::application_t(const std::string& title)
{
    sdl2::init();

    std::tie(_x, _y, _w, _h) = sdl2::get_widest_bounds();
    _pitch  = _w * pixel_size;
    _data   = std::vector<std::uint8_t>(_w * _h * pixel_size, 0);
    _window = SDL_CreateWindow(
        title.c_str(),
        static_cast<int>(_x),
        static_cast<int>(_y),
        static_cast<int>(_w),
        static_cast<int>(_h),
        SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN_DESKTOP |
            SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_INPUT_GRABBED |
            SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_SHOWN);

    if (!_window) {
        throw std::runtime_error(SDL_GetError());
    }

    _renderer = std::make_unique<sdl2::renderer_t>(_window);
    _texture  = std::make_unique<sdl2::texture_t>(
        static_cast<SDL_Renderer*>(*_renderer), _w, _h);

    SDL_WarpMouseInWindow(
        _window, static_cast<int>(_w / 2), static_cast<int>(_h / 2));

    // create state machine
    _tlsm = std::make_unique<sm::tlsm_t>();

    // associate state machine with application
    _tlsm->set_app_ptr(this);
    _tlsm->start();
}

application_t::~application_t()
{
    if (_window) {
        SDL_DestroyWindow(_window);
    }
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
application_t::handle_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: _reactor.on_quit(); break;
        case SDL_KEYDOWN: _reactor.on_keydown(event.key.keysym.sym); break;
        case SDL_MOUSEMOTION:
            _reactor.on_mouse_move(event.motion.x, event.motion.y);
            break;
        default: break;
        }
    }
}

void
application_t::draw_frame()
{
    SDL_UpdateTexture(
        *_texture, nullptr, _data.data(), static_cast<int>(_pitch));
    SDL_RenderCopy(*_renderer, *_texture, nullptr, nullptr);
    SDL_RenderPresent(*_renderer);
}
}
