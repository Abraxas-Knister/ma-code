// the green function
Fourier::spec_t DenseED::green(double step, int counts)
{
    // create timedep scale
    /* the greensfunction is given by
     * i*G = < { c(t) , cd(0) } >
     * = <c(t)cd(0)> + <cd(0)c(t)>
     * = (cd(t)|0>) dot (cd(0)|0>)
     *   + (c(0)|0>) dot (c(t)|0>)
     *
     * this gives a left  state cd(0)|0>
     *              right state  c(0)|0>
     * and then
     * iG = cd(t)|0> dot right
     *      +   left dot c(t)|0>
     */
    Fourier::spec_t tmp;

    tmp.assign(counts,0.0);
    auto state = groundstate;
    const auto left  = Cd(state);
    const auto right =  C(state);
    const auto U     = evolve(step);
    for (int i=0; i<counts; ++i)
    {
        tmp[i] =
         (
          left.dot( Cd(state) ) + ( C(state) ).dot(right)
         )/IU;
        state = U*state;
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
