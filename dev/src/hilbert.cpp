#include "state.hpp"

int bitsSetIn(const int &);

HilbertSpace::HilbertSpace(const int N, const int O)
{
    state_t zeroState{};
    int j = (1<<N) - 1;
    const int last = ((1 << (N+2)) - 1) << (O - N - 2);
    int ct {};
    do {
        ct = bitsSetIn(j);
        if ((ct == N) || (ct == (N+1)) || (ct == (N+2)))
           { zeroState[j]=0; }
    } while (j++ != last);
    zero = zeroState;
}

int bitsSetIn(const int &j)
{
    int ret,u{j};
    for (ret=0;u;ret++) u &= u - 1;
    return ret;
}

int HilbertSpace::Cd(const int &orbital, int &conf) const
{
    const int msk = 1 << orbital;
    int sg {0};
    if (! (conf & msk) )
    {
        int nofJumped = bitsSetIn(conf & (msk - 1));
        sg = 1 - (nofJumped & 1)*2;
        conf |= msk;
    }
    return sg;
}

int HilbertSpace::C(const int &orbital, int &conf) const
{
    const int msk = 1 << orbital;
    int sg {0};
    if (conf & msk)
    {
        int nofJumped = bitsSetIn(conf & (msk - 1));
        sg = 1 - (nofJumped & 1)*2;
        conf &= ~msk;
    }
    return sg;
}
