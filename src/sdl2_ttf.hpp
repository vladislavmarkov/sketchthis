#pragma once
#ifndef SDL2_TTX_HPP
#define SDL2_TTX_HPP

#include <cstdint>
#include <memory>
#include <string>

#include <gsl/gsl>

#include "font.hpp"
#include "sdl2.hpp"

namespace sdl2 {

class renderer_t;
class texture_t;

namespace ttf {

class font_t;

void init();
void quit();

std::unique_ptr<texture_t> render(
    gsl::not_null<renderer_t*>, font_t&, std::string_view text, const color_t&);
}
}

#endif // SDL2_TTX_HPP
