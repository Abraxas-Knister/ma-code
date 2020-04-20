#include "twosite.hpp"

#include <algorithm>
#include <cmath>

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
