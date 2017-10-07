#pragma once
#ifndef SKETCHTHIS_MENUREACTOR_HPP
#define SKETCHTHIS_MENUREACTOR_HPP

#include <memory>

namespace sketchthis {

class application_t;
class reactor_t;

std::unique_ptr<reactor_t> menu_reactor(application_t*);
}

#endif // SKETCHTHIS_MENUREACTOR_HPP
