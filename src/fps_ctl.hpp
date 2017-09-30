#pragma once
#ifndef MISC_FPS_CTL_HPP
#define MISC_FPS_CTL_HPP

#include <chrono>

namespace misc {

class fps_ctl_t {
    std::size_t                           _current_fps      = {0};
    std::size_t                           _frames           = {0};
    std::chrono::steady_clock::time_point _last_update_time = {
        std::chrono::steady_clock::now()};
    std::chrono::milliseconds _sleep_duration = {
        std::chrono::milliseconds::zero()};

public:
    void        update();
    std::size_t get_fps() const;
};
}

#endif // MISC_FPS_CTL_HPP
