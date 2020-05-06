#ifndef TWOSITE_HPP
#define TWOSITE_HPP
#include "config.hpp"

#include "fourier.hpp"
#include "setup.hpp"

#include <vector>

struct Twosite
{
    Setup* setup;
    std::vector<complex> greensfunction;
    double tstep = 0.0;

    Twosite()
        : setup(nullptr)
    { }

    virtual void compute(const double step=1e-6, const int counts=10000)
    {
        tstep = step;
        greensfunction = setup->green(step,counts);
    }
    virtual void ckparams(double&);
};

/* void converge(std::vector<double>* const,Twosite&,Setup*,
              const int,
              const double=1e-5,const int=500);
*/

#endif // guard
