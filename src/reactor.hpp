#pragma once
#ifndef SKETCHTHIS_REACTOR_HPP
#define SKETCHTHIS_REACTOR_HPP

#include <functional>

namespace sketchthis {

struct reactor_t {
    std::function<void(int)> on_keydown = {[](int) {}};
    std::function<void(std::size_t x, std::size_t y)> on_mouse_move = {
        [](std::size_t, std::size_t) {}};
    std::function<void()> on_quit = {[]() {}};

    reactor_t& operator=(reactor_t&&) = default;
    reactor_t& operator=(const reactor_t&) = delete;
    reactor_t()                            = default;
    reactor_t(const reactor_t&)            = delete;
    reactor_t(reactor_t&&)                 = default;
    ~reactor_t()                           = default;

    template <typename KeydownFunc, typename MouseMoveFunc, typename QuitFunc>
    reactor_t(
        KeydownFunc&&   keydown_func,
        MouseMoveFunc&& mousemove_func,
        QuitFunc&&      quit_func)
        : on_keydown(std::forward<KeydownFunc>(keydown_func)),
          on_mouse_move(std::forward<MouseMoveFunc>(mousemove_func)),
          on_quit(std::forward<QuitFunc>(quit_func))
    {
    }
};
}

#endif // SKETCHTHIS_REACTOR_HPP
