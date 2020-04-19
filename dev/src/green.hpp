#ifndef GREENSFUNCTION_HPP
#define GREENSFUNCTION_HPP
#include "config.hpp"

#include "fourier.hpp"
#include "setup.hpp"

struct green
{
    const Setup* setup;
    Fourier* gf;

    green()
        : setup(nullptr) ,
          gf(nullptr)
    { }
    virtual ~green();

    void compute(const double step=1e-6, const int counts=10000);
    void ckparams(double&) const;
    double timestep() const;
};

#endif // guard
