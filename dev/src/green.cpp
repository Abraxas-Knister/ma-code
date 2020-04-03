#include "green.hpp"
#include "setup.hpp"

#include <cmath> 
#include <iostream> 
#include <unsupported/Eigen/FFT> 

green::green(Setup &s)
    : setup (s)
{
    time.reserve(200);
    freq.reserve(200);
    timedep.reserve(200);
    freqdep.reserve(200);
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
    time.resize(counts,0.0);
    int ct=-1;
    for (auto& i : time)
          (++ct , i ? i : i = ct*step); 
    // write freqscale
    freq.clear();
    const double f = 1.0/step;
    for (int i=0; i<counts; i++) { freq.push_back(f*(i-counts/2)); }
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
#include "green-params.inl"
