#pragma once
#ifndef SKETCHTHIS_REACTOR_HPP
#define SKETCHTHIS_REACTOR_HPP

namespace sketchthis {

class reactor_t {
public:
    reactor_t& operator=(reactor_t&&) = default;
    reactor_t& operator=(const reactor_t&) = delete;
    reactor_t()                            = default;
    reactor_t(const reactor_t&)            = delete;
    reactor_t(reactor_t&&)                 = default;
    virtual ~reactor_t()                   = default;

    virtual void on_draw_frame()     = 0;
    virtual void on_keydown(int key) = 0;
    virtual void on_mouse_move(int x, int y) = 0;
    virtual void on_quit() = 0;
};
}

#endif // SKETCHTHIS_REACTOR_HPP
