#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <complex>
#include <map>


// typedefs
using complex = std::complex<double>;
constexpr complex IU = std::complex<double>{0,1};
using state_t = std::map<int,complex>;

// globals
constexpr double relEps {1e-8};
constexpr double absEps {1e-14};
bool areNear( double a, double b=absEps);

#endif
