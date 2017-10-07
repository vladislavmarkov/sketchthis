#pragma once
#ifndef SKETCHTHIS_MENUREACTOR_HPP
#define SKETCHTHIS_MENUREACTOR_HPP

#include <memory>

namespace sdl2 {
class reactor_t;
}

namespace sketchthis {

class application_t;

std::unique_ptr<sdl2::reactor_t> menu_reactor(application_t*);
}

#endif // SKETCHTHIS_MENUREACTOR_HPP
