#pragma once
#ifndef SKETCHTHIS_FUNCTORS_HPP
#define SKETCHTHIS_FUNCTORS_HPP

namespace sketchthis {

struct keydown_func_t {
    keydown_func_t& operator=(const keydown_func_t&) = delete;
    keydown_func_t()                                 = default;
    keydown_func_t(const keydown_func_t&)            = delete;
    virtual ~keydown_func_t()                        = default;
    virtual void
    operator()(int)
    {
    }
};

struct mouse_move_func_t {
    mouse_move_func_t& operator=(const mouse_move_func_t&) = delete;
    mouse_move_func_t()                                    = default;
    mouse_move_func_t(const mouse_move_func_t&)            = delete;
    virtual ~mouse_move_func_t()                           = default;
    virtual void
    operator()(int, int)
    {
    }
};

struct draw_frame_func_t {
    draw_frame_func_t& operator=(const draw_frame_func_t&) = delete;
    draw_frame_func_t()                                    = default;
    draw_frame_func_t(const draw_frame_func_t&)            = delete;
    virtual ~draw_frame_func_t()                           = default;
    virtual void
    operator()()
    {
    }
};

struct quit_func_t {
    quit_func_t& operator=(const quit_func_t&) = delete;
    quit_func_t()                              = default;
    quit_func_t(const quit_func_t&)            = delete;
    virtual ~quit_func_t()                     = default;
    virtual void
    operator()()
    {
    }
};
}

#endif // SKETCHTHIS_FUNCTORS_HPP
