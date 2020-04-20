#ifndef TWOSITE_HPP
#define TWOSITE_HPP
#include "config.hpp"

#include "fourier.hpp"
#include "setup.hpp"

struct Twosite
{
    const Setup* setup;
    Fourier* greensfunction;

    Twosite()
        : setup(nullptr) ,
          greensfunction(nullptr)
    { }
    virtual ~Twosite();

    void compute(const double step=1e-6, const int counts=10000);
    void ckparams(double&) const;
    double timestep() const;
};

#endif // guard
