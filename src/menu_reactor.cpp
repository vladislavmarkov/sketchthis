#include "menu_reactor.hpp"

#include <cassert>

#include <SDL.h>
#include <SDL_ttf.h>

#include "application.hpp"
#include "font.hpp"
#include "reactor.hpp"
#include "renderer.hpp"
#include "sdl2.hpp"
#include "surface.hpp"
#include "texture.hpp"
#include "tlsm.hpp"

namespace sketchthis {

namespace {

class menu_reactor_t : public reactor_t {
    application_t*                   _app  = {nullptr};
    sm::tlsm_t*                      _tlsm = {nullptr};
    std::unique_ptr<sdl2::texture_t> _texture;
    SDL_Rect                         _dstrect = {0, 0, 0, 0};

public:
    menu_reactor_t& operator=(menu_reactor_t&&) = default;
    menu_reactor_t& operator=(const menu_reactor_t&) = delete;
    menu_reactor_t(const menu_reactor_t&)            = delete;
    menu_reactor_t(menu_reactor_t&&)                 = default;

    menu_reactor_t(application_t* app) : _app(app), _tlsm(_app->tlsm())
    {
        assert(_app && _tlsm);

        sdl2::ttf::font_t dejavu(
            "/usr/share/fonts/truetype/dejavu/DejaVuSans-ExtraLight.ttf", 26);

        auto tmp_surface = sdl2::surface_t(
            TTF_RenderText_Blended(
                dejavu,
                "Here could be your main menu...",
                {255, 255, 255, 255}));

        _texture = std::make_unique<sdl2::texture_t>(
            SDL_CreateTextureFromSurface(*_app->renderer(), tmp_surface));

        std::size_t w, h;
        std::tie(w, h) = _texture->get_bounds();
        _dstrect.w = static_cast<int>(w);
        _dstrect.h = static_cast<int>(h);
        std::tie(std::ignore, std::ignore, w, h) = sdl2::get_widest_bounds();
        _dstrect.x = static_cast<int>((w - _dstrect.w) / 2);
        _dstrect.y = static_cast<int>((h - _dstrect.h) / 2);
    }

    void
    on_draw_frame() override
    {
        assert(_app);
        SDL_UpdateTexture(
            *_app->texture(),
            nullptr,
            _app->data().data(),
            static_cast<int>(_app->pitch()));
        SDL_RenderCopy(*_app->renderer(), *_app->texture(), nullptr, nullptr);
        SDL_RenderCopyEx(
            *_app->renderer(),
            *_texture,
            nullptr,
            &_dstrect,
            0.0,
            nullptr,
            SDL_FLIP_NONE);
        SDL_RenderPresent(*_app->renderer());
    }

    void
    on_keydown(int key) override
    {
        assert(_app);
        switch (key) {
        case SDLK_ESCAPE: _app->quit(); break;
        case SDLK_n: _tlsm->process_event(sm::new_canvas()); break;
        case SDLK_d: _tlsm->process_event(sm::discard_canvas()); break;
        default: break;
        }
    }

    void
    on_mouse_move(int, int) override
    {
        // do nothing
    }

    void
    on_quit() override
    {
        assert(_app);
        _app->quit();
    }
};
}

std::unique_ptr<reactor_t>
menu_reactor(application_t* app)
{
    assert(app);
    return std::make_unique<menu_reactor_t>(app);
}
}
