#ifndef DENSEED_HPP
#define DENSEED_HPP
#include "config.hpp"

#include "setup.hpp"

#include <Eigen/Core>

class DenseED : public Setup
{
    /* Hamiltonian is the one for one site and one bath site ie
     * site is occupied with  - (Nsu + Nsd) * mu
     * site has coulomb U(Nsu*Nsd)
     * site has interaction with bath via V * (CsudCbu + CbudCsu + (u->d))
     * bath has occupation via e*(Nbu + Nbd)
     *
     * N C are annihilation / number operators
     * Xb Xs are bath or site operators
     * Xyu Xyd are operators for spin up/down
     *
     * Parameters are only V since halve filling sets the parameters mu = U/2
     * and e=0. (I don't see where this is coming from).
     */
public:
    DenseED(const double iniU, const double iniV)
        : Setup(iniU,iniV)
    {
        set(iniU,iniV);
    }
    void set(const double newU, const double newV) override ;
    Fourier::spec_t green(double,int) const        override ;
private:
    using operator_t = Eigen::Matrix<complex,16,16>;
    using state_t    = Eigen::Vector<complex,16>;

    operator_t H;
    state_t groundstate;

    operator_t evolve(const double t)      const;
    state_t  C(const state_t&,const int=0) const;
    state_t Cd(const state_t&,const int=0) const;

    void setGdstate();
};

#endif // guard
