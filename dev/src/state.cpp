#include "state.hpp"

State::State (HilbertSpace &H)
{
    domain = &H;
    data   = H.zero;
}

void State::Cd(const int orb)
{
    state_t tmp { domain->zero };
    int conf,sg;
    state_t::iterator it;
    for (it = this->data.begin(); it != this->data.end(); it++)
    {
        conf = it->first;
        sg = domain->Cd(orb,conf);
        if (sg) tmp[conf] += it->second * static_cast<complex>(sg);
    }
    data.swap(tmp);
}

void  State::C(const int orb)
{
    state_t tmp { domain->zero };
    int conf,sg;
    state_t::iterator it;
    for (it = this->data.begin(); it != this->data.end(); it++)
    {
        conf = it->first;
        sg = domain->C(orb,conf);
        if (sg) tmp[conf] += it->second * static_cast<complex>(sg);
    }
    data.swap(tmp);
}
