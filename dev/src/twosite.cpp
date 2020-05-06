#include "twosite.hpp"

#include <algorithm>
#include <cmath>
#include <dlib/optimization.h>
#include <iostream>

#include "twosite-params.inl"
/* implements ckparams and timestep
 */

/*
void converge( std::vector<double>* const ret,
               Twosite& calc, Setup* s,
               const int counts,
               const double prec, const int maxiter)
{
    if (!s)
          throw "trying to converge with no method";
    if (calc.tstep == 0.0)
          throw "Didn't set time!";
    calc.setup = s;

    std::vector<double> paramV;
    if (ret)
    {
        paramV.resize(maxiter);
        paramV[0] = s->getV();
    }
    int ct{ 0 };
    double curV {0.0}, oldV;

    do {
        oldV=curV;
        calc.compute(calc.tstep,counts);
        calc.ckparams(curV);
        s->set(s->getU(),curV);
        if (ret)
              paramV[ct]=curV;
    } while ( (++ct < maxiter ) && !areNear(curV,oldV,prec));
    std::cerr << (ct==maxiter ? "Warn: many cycles\n" : "");

    calc.setup = nullptr;
    if (ret)
    {
        paramV.resize(ct);
        ret->swap(paramV);
    }
}

*/
