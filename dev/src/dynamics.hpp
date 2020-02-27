#ifndef DYNAMICS_HPP
#define DYNAMICS_HPP
#include "config.hpp"

#include "sparse.hpp"
#include "state.hpp"

struct Hamiltonian
{
    /* Will do this:
     * cdcData stores the CdC terms (for now only the double and I only allow
     * constant Hamiltonians.
     *
     * intData stores the nn terms.
     */

    Sparse_t<double> cdcData;
    Sparse_t<double> intData;
    void actOn(State &v) const;
};

#endif // guard
