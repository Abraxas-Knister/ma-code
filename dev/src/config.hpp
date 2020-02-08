#ifndef CONFIG_HPP
#define CONFIG_HPP

#define DEBUG_2 // 0 for off, 2 is maximal
#include "debug.hpp"

// instead of typedefs
// using index_t = std::int32_t; // only types not things like constexpr, static

constexpr double relEps {1e-8};
constexpr double absEps {1e-14};
bool areNear( double a, double b );

#endif
