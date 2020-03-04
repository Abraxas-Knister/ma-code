#ifndef M_SETUP_HPP
#define M_SETUP_HPP
#include "config.hpp"

#include <Eigen/Dense>

using m_operator_t = Eigen::Matrix<double,16,16>;
using m_state_t    = Eigen::Vector<complex,16>;

struct Setup
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
    double U,V;
    m_operator_t H;
    m_state_t state;
    Setup(const double iniU, const double iniV);
    void evolve(const double t);
    void actWithC(const int orb);
    void actWithCd(const int orb);
    void updateH(const double newU, const double newV);
    m_state_t gdstate() const;
};

#endif // guard
