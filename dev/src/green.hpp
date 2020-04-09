#ifndef GREENSFUNCTION_HPP
#define GREENSFUNCTION_HPP
#include "config.hpp"

#include "setup.hpp"
#include <vector>

struct green
{
    const Setup &setup;

    std::vector<double> time;
    std::vector<double> freq;
    std::vector<complex> timedep;
    std::vector<complex> freqdep;

    green(Setup &);

    void compute(const double step=1e-6, const int counts=10000);
    void ckparams(double&,double&) const;
    double timestep() const;

    friend std::ostream& operator<< (std::ostream &,const green &);
};

#endif // guard
