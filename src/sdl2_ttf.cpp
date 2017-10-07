#include "sdl2_ttf.hpp"

#include <cassert>
#include <cstdlib>
#include <stdexcept>

#include <SDL_ttf.h>

#include "renderer.hpp"
#include "surface.hpp"
#include "texture.hpp"

namespace sdl2 {

namespace ttf {

void
init()
{
    if (TTF_Init() < 0) {
        throw std::runtime_error(TTF_GetError());
    }
    std::atexit(TTF_Quit);

    const SDL_version* linked_version = TTF_Linked_Version();
    SDL_version        compiled_version;
    SDL_TTF_VERSION(&compiled_version);

    assert(linked_version->major == compiled_version.major);
    assert(linked_version->minor == compiled_version.minor);
    assert(linked_version->patch == compiled_version.patch);
}

std::unique_ptr<texture_t>
render(
    renderer_t*        renderer,
    font_t&            font,
    const std::string& text,
    const color_t&     color)
{
    assert(renderer && !text.empty());
    auto tmp_surface =
        sdl2::surface_t(TTF_RenderText_Blended(font, text.c_str(), color));
    return std::make_unique<sdl2::texture_t>(
        SDL_CreateTextureFromSurface(*renderer, tmp_surface));
}
}
}