Setup::state_t Setup::C(const Setup::state_t& state, const int orb) const
{
    state_t tmp = state_t::Zero();
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
    return tmp;
}

Setup::state_t Setup::Cd(const Setup::state_t& state, const int orb) const
{
    state_t tmp = state_t::Zero();
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
    return tmp;
}

Setup::operator_t Setup::evolve(const double t) const
{
     return (- IU * H * t).exp();
}
