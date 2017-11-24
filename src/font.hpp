#pragma once
#ifndef SDL2_TTF_FONT_HPP
#define SDL2_TTF_FONT_HPP

#include <functional>
#include <memory>
#include <string_view>

struct _TTF_Font;
typedef struct _TTF_Font TTF_Font;

namespace sdl2 {

namespace ttf {

class font_t {
    std::unique_ptr<TTF_Font, std::function<void(TTF_Font*)>> _font;

public:
    font_t(std::string_view file, std::size_t ptsize);
    ~font_t();

    operator TTF_Font*();
};
}
}

#endif // SDL2_TTF_FONT_HPP
