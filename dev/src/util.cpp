#include "config.hpp"

#include <algorithm>    // for std::max
#include <cmath>        // for std::abs
#include <fstream>      // for std::ofstream(::app)

bool areNear( double a, double b )
// mostly relative comparison of floating point values
{
    double diff = std::abs(a-b);
    bool ret { diff <= absEps };
    if (ret) {
        return true;
    }
    ret = ( diff <= (std::max(std::abs(a), std::abs(b)) * relEps) );
    return ret;
}
