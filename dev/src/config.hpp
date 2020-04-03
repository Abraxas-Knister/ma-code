#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <complex>
#include <cmath> 
#include <map>


// typedefs
using complex = std::complex<double>;
using state_t = std::map<int,complex>;

// globals
constexpr double relEps {1e-8};
constexpr double absEps {1e-14};
bool areNear( double a, double b=absEps,double rel=relEps,double abs=absEps);

const double PI = std::acos(-1);
constexpr complex IU = std::complex<double>{0,1};

#endif
