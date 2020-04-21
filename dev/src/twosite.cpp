#include "twosite.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>

#include "twosite-params.inl"
/* implements ckparams and timestep
 */

Twosite::~Twosite() { delete greensfunction; }

void Twosite::compute(const double step, const int counts)
{
    Fourier::spec_t tmp { setup->green(step,counts) };
    if (!greensfunction)
          greensfunction = new Fourier(tmp,step);
    else
          greensfunction->update(tmp,step);
}

void converge( std::vector<double>* const ret,
               Twosite& calc, Setup* s,
               const double prec, double step, const int maxiter)
{
    if (!s)
          throw "trying to converge with no method";
    calc.setup = s;

    std::vector<double> paramV;
    if (ret)
    {
        paramV.resize(maxiter);
        paramV[0] = s->getV();
    }
    int ct{ 0 }, cur{ 0 };
    double curV {0.0}, oldV;

    do {
        oldV=curV;
        calc.compute(step);
        calc.ckparams(curV);
        s->set(s->getU(),curV);
        step = calc.timestep();
        if (ret)
              paramV[++cur]=curV;
    } while ( (++ct < maxiter ) && !areNear(curV,oldV,prec));
    std::cerr << (ct==maxiter ? "Warn: many cycles\n" : "");

    calc.setup = nullptr;
    if (ret)
    {
        paramV.resize(ct);
        ret->swap(paramV);
    }
}
