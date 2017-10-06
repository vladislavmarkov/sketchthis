#pragma once
#ifndef SDL2_TTF_FONT_HPP
#define SDL2_TTF_FONT_HPP

#include <functional>
#include <memory>
#include <string>

struct _TTF_Font;
typedef struct _TTF_Font TTF_Font;

namespace sdl2 {

namespace ttf {

class font_t {
    std::unique_ptr<TTF_Font, std::function<void(TTF_Font*)>> _font;

public:
    font_t(const std::string& file, std::size_t ptsize);
    ~font_t();

    operator TTF_Font*();
};
}
}

#endif // SDL2_TTF_FONT_HPP
