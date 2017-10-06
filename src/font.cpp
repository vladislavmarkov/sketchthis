#include "font.hpp"

#include <cstdint>

#include <SDL_ttf.h>

namespace sdl2 {

namespace ttf {

font_t::font_t(const std::string& file, std::size_t ptsize)
    : _font(
          TTF_OpenFont(file.c_str(), static_cast<int>(ptsize)),
          [](TTF_Font* ptr) { TTF_CloseFont(ptr); })
{
    if (!_font) {
        std::runtime_error("failed to create font object");
    }
}

font_t::~font_t() = default;

font_t::operator TTF_Font*() { return _font.get(); }
}
}