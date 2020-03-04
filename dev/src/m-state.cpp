#include "m-setup.hpp"
#include <unsupported/Eigen/MatrixFunctions>

void Setup::actWithC(const int orb)
{
    m_state_t tmp = m_state_t::Zero();
    if (orb == 0)
    {
        for (int i=0; i<16; i++)
        {
            if (i&1) { tmp(i-1) += state(i); }
        }
    }
    if (orb == 1)
    {
        for (int i=0; i<16; i++)
        {
            double sg = 1-2*(i&1);
            if (i&2) { tmp(i-2) += sg*state(i); }
        }
    }
    state.swap(tmp);
}

void Setup::actWithCd(const int orb)
{
    m_state_t tmp = m_state_t::Zero();
    if (orb == 0)
    {
        for (int i=0; i<16; i++)
        {
            if (!(i&1)) { tmp(i+1) += state(i); }
        }
    }
    if (orb == 1)
    {
        for (int i=0; i<16; i++)
        {
            double sg = 1-2*(i&1);
            if (!(i&2)) { tmp(i+2) += sg*state(i); }
        }
    }
    state.swap(tmp);
}

void Setup::evolve(const double t)
{
    m_state_t tmp;
    tmp = (-H*t*IU).exp() * state;
    state.swap(tmp);
}
