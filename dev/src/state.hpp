#ifndef STATE_HPP
#define STATE_HPP

#include "config.hpp"
#include <map>
#include <vector>

struct HilbertSpace
{
    std::vector<int>  base1;
    std::map<int,int> ind1;
    std::vector<int>  base2;
    std::map<int,int> ind2;
    /* these store the bases for the nofParticles and nofParticles+1 Hilbert
     * spaces. One can acess the bitmask for the base state with a given index
     * via base1/2.at(index) and get the index for the element via
     * ind1/2[element]
     */
    HilbertSpace(const int N, const int O);
    int Cd(const int &orbital, int &baseIndex) const;
    int  C(const int &orbital, int &baseIndex) const;
    /* these calculate the result of acting with the creator/annihilator for
     * orbital with number "orbital" on the base element with number
     * "baseIndex".
     *
     * they give back the sign of the resulting base element and store the base
     * Index the baseIndex variable. 0 is returned if the operator destroys the
     * state.
     *
     * the base element is taken from the respective subspace (ie nofParticles
     * HilbertSpace for Cd and nofParticle+1 HilberSpace for C)
     */
};

struct State
{
    HilbertSpace *domain;
    std::vector<complex> data1;
    std::vector<complex> data2;
    void Cd(const int orb);
    void  C(const int orb);
};

#endif // guard
