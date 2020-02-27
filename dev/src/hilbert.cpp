#include "state.hpp"

int bitsSetIn(const int &);
void createBase(const int,const int,std::vector<int> &,std::map<int,int> &);

HilbertSpace::HilbertSpace(const int N, const int O)
{
    createBase(N  ,O,base1,ind1);
    createBase(N+1,O,base2,ind2);
}

void createBase(const int N, const int O, std::vector<int> &b, std::map<int,int> &i)
{
    b.clear(); i.clear();
    int j = (1<<N) - 1;
    const int last = j << (O - N);
    int ct=0;
    do {
        if (bitsSetIn(j) == N)
        {
            b.push_back(j);
            i[j] = ct++;
        }
    } while (j++ != last);
}

int bitsSetIn(const int &j)
{
    int ret,u{j};
    for (ret=0;u;ret++) u &= u - 1;
    return ret;
}

int HilbertSpace::Cd(const int &orbital, int &baseIndex) const
{
    const int element = base1[baseIndex];
    const int msk = 1 << orbital;
    int sg {0};
    if (! (element & msk) )
    {
        baseIndex = ind2.at(element | msk);
        int nofJumped = bitsSetIn( element & (msk -1) );
        sg = 1-(nofJumped & 1)*2;
    }
    return sg;
}

int HilbertSpace::C(const int &orbital, int &baseIndex) const
{
    const int element = base2[baseIndex];
    const int msk = 1 << orbital;
    int sg {0};
    if (element & msk)
    {
        baseIndex = ind1.at(element & ~msk);
        int nofJumped = bitsSetIn( element & (msk -1) );
        sg = 1-(nofJumped & 1)*2;
    }
    return sg;
}
