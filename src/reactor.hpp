#pragma once
#ifndef SDL2_REACTOR_HPP
#define SDL2_REACTOR_HPP

#include <cstdint>

#include <gsl/gsl>

#include "sdl2.hpp"

namespace sdl2 {

class reactor_t {
public:
    reactor_t& operator=(reactor_t&&) = default;
    reactor_t& operator=(const reactor_t&) = delete;
    reactor_t()                            = default;
    reactor_t(const reactor_t&)            = delete;
    reactor_t(reactor_t&&)                 = default;
    virtual ~reactor_t()                   = default;

    virtual void on_draw_frame()               = 0;
    virtual void on_keydown(keycode_t key)     = 0;
    virtual void on_mouse_move(const point_t&) = 0;
    virtual void on_quit()                     = 0;
};

void handle_events(gsl::not_null<reactor_t*>);
}

#endif // SDL2_REACTOR_HPP
