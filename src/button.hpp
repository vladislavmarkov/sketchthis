#ifndef SDL2_BUTTON_HPP
#define SDL2_BUTTON_HPP

#include <functional>
#include <memory>
#include <tuple>
#include <type_traits>

#include <gsl/gsl>

#include "sdl2.hpp"

namespace sdl2 {

class renderer_t;
class texture_t;

class button_t {
    std::function<void()>            _func = {[]() {}};
    std::unique_ptr<sdl2::texture_t> _texture;

public:
    button_t(gsl::not_null<renderer_t*>, const rect_t& rect);

    template <typename FuncType>
    void
    set_on_click(FuncType&& click_func)
    {
        static_assert(std::is_invocable_v<FuncType>);
        _func = std::forward<FuncType>(click_func);
    }

    ~button_t();
};
} // namespace sdl2

#endif // SDL2_BUTTON_HPP
