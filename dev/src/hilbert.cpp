#include "state.hpp"

int bitsSetIn(const int &);

HilbertSpace::HilbertSpace(const int N, const int O)
{
    // HilbertSpace data
    nofParticles = N;
    zero = {};
    // compute final zero
    constexpr complex ZERO { static_cast<complex>(0) };
    state_t zeroState{};
    const int last = ((1 << (N+1)) - 1) << (O - N - 1);
    int j = (1<<(N-1)) - 1;
    int ct {};
    do {
        ct = bitsSetIn(j);
        if ((ct == N) || (ct == (N-1)) || (ct == (N+1)))
           { zeroState[j] = ZERO; }
    } while (j++ != last);
    // swap is better than copy!
    zero.swap(zeroState);
}

int HilbertSpace::Cd(const int &orbital, int &conf) const
{
    const int msk = 1 << orbital;
    int sg {0};
    if (! (conf & msk) && (bitsSetIn(conf) < (nofParticles + 1)))
    {
        const int nofJumped = bitsSetIn(conf & (msk - 1));
        sg = 1 - (nofJumped & 1)*2;
        conf |= msk;
    }
    return sg;
}

int HilbertSpace::C(const int &orbital, int &conf) const
{
    const int msk = 1 << orbital;
    int sg {0};
    if ((conf & msk) && (bitsSetIn(conf) > (nofParticles - 1)))
    {
        const int nofJumped = bitsSetIn(conf & (msk - 1));
        sg = 1 - (nofJumped & 1)*2;
        conf &= ~msk;
    }
    return sg;
}

int bitsSetIn(const int &j)
{
    int ret,u{j};
    for (ret=0;u;ret++) u &= u - 1;
    return ret;
}
