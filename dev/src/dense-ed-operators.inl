DenseED::state_t DenseED::C(const DenseED::state_t& state, const int orb) const
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

DenseED::state_t DenseED::Cd(const DenseED::state_t& state, const int orb) const
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

DenseED::operator_t DenseED::evolve(const double t) const
{
     return (- IU * H * t).exp();
}
