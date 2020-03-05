#ifndef GREENSFUNCTION_HPP
#define GREENSFUNCTION_HPP
#include "config.hpp"

#include "m-setup.hpp"
#include <vector>

struct m_gf
{
    Setup *setup;
    std::vector<double> time;
    std::vector<double> freq;
    std::vector<complex> timedep0;
    std::vector<complex> timedep1;
    std::vector<complex> freqdep0;
    std::vector<complex> freqdep1;
    m_gf(Setup &);
    void compute(const double step=0.1, const int counts=1000);
    friend std::ostream& operator<< (std::ostream &out, const m_gf &gf);
};

#endif // guard
