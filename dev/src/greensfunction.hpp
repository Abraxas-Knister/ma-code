#ifndef GREENSFUNCTION_HPP
#define GREENSFUNCTION_HPP
#include "config.hpp"

#include "m-setup.hpp"
#include <vector>

struct m_gf
{
    Setup *setup;
    std::vector<double> time;
    std::vector<double> real0;
    std::vector<double> imag0;
    std::vector<double> real1;
    std::vector<double> imag1;
    m_gf(Setup &);
    void compute(const double begin=0, const double end=100, const double step=0.1);
    friend std::ostream& operator<< (std::ostream &out, const m_gf &gf);
};

#endif // guard
