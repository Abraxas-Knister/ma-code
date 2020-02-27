#ifndef CONFIG_HPP
#define CONFIG_HPP

#define DEBUG_2 // 0 for off, 2 is maximal
#include "debug.hpp"
#include <complex>

// typedefs
using complex = std::complex<double>;

// globals
constexpr double relEps {1e-8};
constexpr double absEps {1e-14};
bool areNear( double a, double b );

#endif
