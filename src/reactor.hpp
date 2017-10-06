#pragma once
#ifndef SKETCHTHIS_REACTOR_HPP
#define SKETCHTHIS_REACTOR_HPP

#include <functional>
#include <memory>

namespace sketchthis {

struct keydown_func_t;
struct mouse_move_func_t;
struct draw_frame_func_t;
struct quit_func_t;

class reactor_t {
    using keydown_func_ptr    = std::unique_ptr<keydown_func_t>;
    using mouse_move_func_ptr = std::unique_ptr<mouse_move_func_t>;
    using draw_frame_func_ptr = std::unique_ptr<draw_frame_func_t>;
    using quit_func_ptr       = std::unique_ptr<quit_func_t>;

    keydown_func_ptr    _on_keydown;
    mouse_move_func_ptr _on_mouse_move;
    draw_frame_func_ptr _on_draw_frame;
    quit_func_ptr       _on_quit;

public:
    reactor_t& operator=(reactor_t&&);
    reactor_t& operator=(const reactor_t&) = delete;
    reactor_t();
    reactor_t(const reactor_t&) = delete;
    reactor_t(reactor_t&&);
    ~reactor_t();

    reactor_t(
        keydown_func_ptr&&,
        mouse_move_func_ptr&&,
        draw_frame_func_ptr&&,
        quit_func_ptr&&);

    void on_keydown(int key);
    void on_mouse_move(int x, int y);
    void on_draw_frame();
    void on_quit();
};
}

#endif // SKETCHTHIS_REACTOR_HPP
