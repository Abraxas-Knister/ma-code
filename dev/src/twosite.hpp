#ifndef TWOSITE_HPP
#define TWOSITE_HPP
#include "config.hpp"

#include "fourier.hpp"
#include "setup.hpp"

#include <vector>

struct Twosite
{
    Setup* setup;
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

void converge(std::vector<double>* const,Twosite&,Setup*,const double,double=5e-3,const int=500);

#endif // guard
