#pragma once
#ifndef SDL2_BUTTON_HPP
#define SDL2_BUTTON_HPP

#include <functional>
#include <memory>

namespace sdl2 {

class renderer_t;
class texture_t;

class button_t {
    std::function<void()>            _func = {[]() {}};
    std::unique_ptr<sdl2::texture_t> _texture;

public:
    button_t(
        renderer_t*,
        std::size_t x,
        std::size_t y,
        std::size_t w,
        std::size_t h);

    template <typename FuncType>
    void
    set_on_click(FuncType&& click_func)
    {
        _func = std::forward<FuncType>(click_func);
    }

    ~button_t();
};
}

#endif // SDL2_BUTTON_HPP
