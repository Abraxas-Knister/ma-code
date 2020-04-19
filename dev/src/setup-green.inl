Fourier::spec_t Setup::green(double step, int counts) const
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
