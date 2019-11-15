#ifndef SDL2_WRAPPER_HPP
#define SDL2_WRAPPER_HPP

#include <array>
#include <cstdint>
#include <tuple>

#include <gsl/gsl>

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>

namespace sdl2 {

using area_t = std::array<int, 2>;

using color_t   = SDL_Color;
using keycode_t = SDL_Keycode;
using point_t   = SDL_Point;
using rect_t    = SDL_Rect;

class window_t;

constexpr uint8_t pixel_size = {4}; // rgb + alpha = 4 bytes

void init();
void quit();

rect_t get_widest_bounds();

void warp_mouse(gsl::not_null<window_t*>, const point_t&);
} // namespace sdl2

#endif // SDL2_WRAPPER_HPP
