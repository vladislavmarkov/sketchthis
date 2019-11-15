#ifndef TERM_hpp
#define TERM_hpp

#include <exception> // std::terminate
#include <iostream>  // std::cerr

#define TERM(msg)                                                   \
    {                                                               \
        std::cerr << "(TERMINATE): resason - " << msg << std::endl; \
        std::terminate();                                           \
    }

#endif // TERM_hpp
