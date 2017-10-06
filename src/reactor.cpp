#include "reactor.hpp"

#include "functors.hpp"

namespace sketchthis {

reactor_t& reactor_t::operator=(reactor_t&&) = default;

reactor_t::reactor_t() = default;

reactor_t::reactor_t(reactor_t&&) = default;

reactor_t::reactor_t(
    keydown_func_ptr&&    arg_keydown_func,
    mouse_move_func_ptr&& arg_mouse_move_func,
    draw_frame_func_ptr&& arg_draw_frame_func,
    quit_func_ptr&&       arg_quit_func)
    : _on_keydown(std::move(arg_keydown_func)),
      _on_mouse_move(std::move(arg_mouse_move_func)),
      _on_draw_frame(std::move(arg_draw_frame_func)),
      _on_quit(std::move(arg_quit_func))
{
}

reactor_t::~reactor_t() = default;

void
reactor_t::on_keydown(int key)
{
    if (_on_keydown) {
        _on_keydown->operator()(key);
    }
}

void
reactor_t::on_mouse_move(int x, int y)
{
    if (_on_mouse_move) {
        _on_mouse_move->operator()(x, y);
    }
}

void
reactor_t::on_draw_frame()
{
    if (_on_draw_frame) {
        _on_draw_frame->operator()();
    }
}

void
reactor_t::on_quit()
{
    if (_on_quit) {
        _on_quit->operator()();
    }
}
}
