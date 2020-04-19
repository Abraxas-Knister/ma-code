#include "setup.hpp"

#include <cmath>
#include <iostream>
#include <Eigen/Eigenvalues>
#include <unsupported/Eigen/MatrixFunctions>

#include "setup-operators.inl"
#include "setup-gdstate.inl"
#include "setup-green.inl"

int sg(int msk, int orb);
void Setup::set (const double newU, const double newV)
{
    U=newU;
    V=newV;
    operator_t tmp = operator_t::Zero();  
    int j {};
    for (int i = 0; i<16; i++ )
    {
        if (i & 1) tmp(i,i) += -.5*U;
        if (i & 2) tmp(i,i) += -.5*U;
        if (i & 1 && i & 2) tmp(i,i) += U;
        if (!(i & 4) && i & 1)
        {
            j = (i | 4) & ~1;
            tmp(j,i) += V*sg(i,1);
        }
        if (!(i & 8) && i & 2)
        {
            j = (i | 8) & ~2;
            tmp(j,i) += V*sg(i,2);
        }
        if (!(i & 1) && i & 4)
        {
            j = (i | 1) & ~4;
            tmp(j,i) += V*sg(i,1);
        }
        if (!(i & 2) && i & 8)
        {
            j = (i | 2) & ~8;
            tmp(j,i) += V*sg(i,2);
        }
    }
    H.swap(tmp);
    setGdstate();
}
inline int sg(int msk, int orb)
{
    bool has = msk & (1<<orb);
    return 1-2*has;
}
