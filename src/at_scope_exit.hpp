#pragma once
#ifndef AT_SCOPE_EXIT_HPP
#define AT_SCOPE_EXIT_HPP

namespace nonstd {

template <typename FuncType>
class at_scope_exit {
    std::function<FuncType> _func;

public:
    at_scope_exit& operator=(at_scope_exit&&) = default;
    at_scope_exit& operator=(const at_scope_exit&) = delete;
    at_scope_exit(at_scope_exit&&)                 = default;
    at_scope_exit(const at_scope_exit&)            = delete;
    template <typename FuncTypeAlt>
    at_scope_exit(FuncTypeAlt&& func) : _func(std::forward<FuncTypeAlt>(func))
    {
    }
    ~at_scope_exit() { _func(); }
};
}

#endif // AT_SCOPE_EXIT_HPP
