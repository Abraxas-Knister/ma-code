// the green function
Fourier::spec_t DenseED::green(double step, int counts)
{
    // create timedep scale
    /* the greensfunction is given by
     * i*G = < { c(t) , cd(0) } >
     * = <c(t)cd(0)> + <cd(0)c(t)>
     * = < Ud^n C U^n Cd + Cd Ud^n C U^n >
     * =  dot ( Cd U^n |0> , U^n Cd |0> )
     *  + dot ( U^n C  |0> , C  U^n |0> )
     *
     * then with
     *    left  =   C |0>
     *    right =  Cd |0>
     *
     * iG( n t )
     *   =  dot( Cd U^n |0>  ,   U^n right)
     *    + dot(    U^n left , C U^n |0>  )
     */
    Fourier::spec_t tmp;

    tmp.assign(counts,0.0);
    auto state = groundstate;
    auto left  =  C(state);
    auto right = Cd(state);
    const auto U = evolve(step);
    for (int i=0; i<counts; ++i)
    {
        tmp[i] =
         (
          left.dot( C(state) ) + ( Cd(state) ).dot(right)
         )/IU;
        state = U*state;
        left  = U*left;
        right = U*right;
    }
    return tmp;
}

// the set function
inline int sg(int msk, int orb)
{
    bool has = msk & (1<<orb);
    return 1-2*has;
}
void DenseED::set (const double newU, const double newV)
{
    U=newU;
    V=newV;
    operator_t tmp = operator_t::Zero();
    int j {};
    for (int i = 0; i<16; i++ )
    {
        // - mu N_imp↓
        if (i & 1) tmp(i,i) += -.5*U;
        // - mu N_imp↑
        if (i & 2) tmp(i,i) += -.5*U;
        // +  U N_imp↑*N_imp↓
        if (i & 1 && i & 2) tmp(i,i) += U;
        // + V * imp↓->bath↓
        if (!(i & 4) && i & 1)
        {
            j = (i | 4) & ~1;
            tmp(j,i) += V*sg(i,1);
            // multiply by -1 if i has bit 1 set (imp ↑)
        }
        if (!(i & 1) && i & 4)
        {
            j = (i | 1) & ~4;
            tmp(j,i) += V*sg(i,1);
        }
        // + V * imp↑->bath↑
        if (!(i & 8) && i & 2)
        {
            j = (i | 8) & ~2;
            tmp(j,i) += V*sg(i,2);
            // multiply by -1 if i has bit 1 set (bath ↓)
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
