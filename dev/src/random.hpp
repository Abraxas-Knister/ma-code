#ifndef RANDOM_HPP
#define RANDOM_HPP
#include "config.hpp"

namespace Random
{
    extern bool seeded;
    inline void check () { if (!seeded) throw "didn't seed"; }
    // these toggle seeded
    void seed();
    void static_seed(int);
    // these each call ckeck()
    double rand();
    double grand(double,double);
}

#endif // guard
