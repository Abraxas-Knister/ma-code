#include "green.hpp"
#include "setup.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <unsupported/Eigen/FFT>

#include "green-params.inl"
/* implements ckparams and timestep
 */

green::green(Setup &s)
    : setup (s)
{
    time.reserve(2000);
    freq.reserve(2000);
    timedep.reserve(2000);
    freqdep.reserve(2000);
}

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
    timedep.assign(counts,0.0);
    auto state = setup.groundstate;
    const auto left  = setup.Cd(state);
    const auto right = setup.C(state);
    const auto U = setup.evolve(step);
    for (int i=0; i<counts; ++i)
    {
        timedep[i] =
         (
          left.dot(setup.Cd(state)) + (setup.C(state)).dot(right)
         )/IU;
        state = U*state;
    }
    // create freqdep scale
    freqdep.clear();
    static Eigen::FFT<double> fft;
    fft.fwd(freqdep,timedep);

    // write timescale
    time.resize(counts);
    int ct=-1;
    for (auto& i : time)
          i = ++ct * step; 
    // write freqscale
    freq.resize(counts);
    const double f = 1.0/(counts*step);
    for (int i=0; i<counts; i++)
    {
        int j = ( i < counts/2 ? i : i-counts);
        freq[i] = f * j;
    }
}

std::ostream& operator<< (std::ostream &out, const green &gf)
{
    for (std::size_t i=0; i<gf.time.size(); i++)
    {
        out << gf.time[i] << ' ' 
            << gf.timedep[i].real() << ' ' << gf.timedep[i].imag() << ' '
            << gf.freq[i] << ' ' 
            << gf.freqdep[i].real() << ' ' << gf.freqdep[i].imag() << '\n';
    }
    return out;
}
