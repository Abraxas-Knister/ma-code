#ifndef STATE_HPP
#define STATE_HPP

#include "config.hpp"

struct State;
struct HilbertSpace
{
    state_t zero;
    /* O stores an all zero vector in the nofParticles, +0,+1,+2 spaces
     * This is needed to be able to store the regal base elements of states when
     * one has a particle conserving Interaction and only wants to calculate two
     * point functions.
     */
    HilbertSpace(const int N, const int O);
    int Cd(const int &orbital, int &conf) const;
    int  C(const int &orbital, int &conf) const;
    /* these calculate the result of acting with the creator/annihilator for
     * orbital with number "orbital" on the base element with configuration
     * "conf", modifying the conf in the process.
     *
     * they give back the sign of the resulting base element and store the base
     * Index the baseIndex variable. 0 is returned if the operator destroys the
     * state.
     */
};

struct State
{
    HilbertSpace *domain;
    state_t data;
    State (HilbertSpace &);
    void Cd(const int orb);
    void  C(const int orb);
};

#endif // guard
