#include "green.hpp"
#include "setup.hpp"

#include <algorithm>
#include <cmath>

#include "green-params.inl"
/* implements ckparams and timestep
 */

green::green(Setup &s)
    : setup (s),
      gf(nullptr)
{ }

green::~green() { delete gf; }

void green::compute(const double step, const int counts)
{
    // create timedep scale
    /* the greensfunction is given by
     * i*G = < { c(t) , cd(0) } >
     * = <c(t)cd(0)> + <cd(0)c(t)>
     * = (cd(t)|0>) dot (cd(0)|0>)
     *   + (c(0)|0>) dot (c(t)|0>)
     *
     * this gives a left  state cd(0)|0>
     *              right state  c(0)|0>
     * and then
     * iG = cd(t)|0> dot right
     *      +   left dot c(t)|0>
     */
    Fourier::spec_t tmp;
    tmp.assign(counts,0.0);
    auto state = setup.groundstate;
    const auto left  = setup.Cd(state);
    const auto right = setup.C(state);
    const auto U = setup.evolve(step);
    for (int i=0; i<counts; ++i)
    {
        tmp[i] =
         (
          left.dot(setup.Cd(state)) + (setup.C(state)).dot(right)
         )/IU;
        state = U*state;
    }
    if (!gf)
          gf = new Fourier(tmp,step);
    else
          gf->update(tmp,step);
}
