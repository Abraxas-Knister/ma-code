#include "green.hpp"

#include <algorithm>
#include <cmath>

#include "green-params.inl"
/* implements ckparams and timestep
 */

green::~green() { delete gf; }

void green::compute(const double step, const int counts)
{
    Fourier::spec_t tmp { setup->green(step,counts) };
    if (!gf)
          gf = new Fourier(tmp,step);
    else
          gf->update(tmp,step);
}
