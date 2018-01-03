#include "font.hpp"

#include <cstdint>
#include <experimental/filesystem>
#include <regex>
#include <stdexcept>

#include <SDL_ttf.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <gsl/gsl>

namespace sdl2::ttf {

namespace {

namespace fs = std::experimental::filesystem;
using namespace std::literals::string_literals;

std::vector<std::string>
get_font_dirs()
{
    constexpr char fonts_conf[] = "/etc/fonts/fonts.conf";
    if (!fs::exists(fonts_conf) || !fs::is_regular_file(fonts_conf)) {
        throw std::runtime_error(
            "Error: Failed to find fonts configuration file");
    }

    std::vector<std::string> font_dirs;

    namespace pt = boost::property_tree;
    pt::ptree fonts_conf_tree;
    pt::read_xml(fonts_conf, fonts_conf_tree, pt::xml_parser::no_comments);
    for (const auto font_conf : fonts_conf_tree.get_child("fontconfig")) {
        if (font_conf.first == "dir") {
            const auto font_dir = font_conf.second.data();
            if (fs::exists(font_dir) && fs::is_directory(font_dir)) {
                font_dirs.push_back(font_dir);
            }
        }
    }

    font_dirs.shrink_to_fit();
    return font_dirs;
}

std::optional<std::string>
find_font_file(std::string_view basefile)
{
    assert(!basefile.empty());
    const auto dirs = get_font_dirs();
    for (const auto& dir : dirs) {
        auto matching_pattern = std::regex(
            dir + "[/a-zA-Z0-9-_]+"s + std::string(basefile) + "\\.ttf");
        for (auto& p : fs::recursive_directory_iterator(dir)) {
            std::smatch match;
            const auto  str = p.path().string();
            std::regex_search(str, match, matching_pattern);
            if (!match.empty()) {
                return match[0];
            }
        }
    }

    return {};
}
}

font_t& font_t::operator=(font_t&&) = default;

font_t::font_t(font_t&&) = default;

font_t::font_t(std::string_view basefile, std::size_t ptsize)
{
    auto filename = find_font_file(basefile);
    if (!filename || filename->empty()) {
        throw std::runtime_error("Error: Failed to find font file");
    }

    _font = decltype(_font)(
        TTF_OpenFont(filename->c_str(), gsl::narrow<int>(ptsize)),
        [](TTF_Font* ptr) { TTF_CloseFont(ptr); });

    if (!_font) {
        std::runtime_error("Error: Failed to create font object");
    }
}

font_t::~font_t() = default;

font_t::operator TTF_Font*() { return _font.get(); }
}
