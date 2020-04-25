Qmeth& Qmeth::prepare()
{
    /* set 0 to down
     * set 1-4 to groundstate of
     * U( n_(1-2) * n_(3-4) ) - U/2 ( n_(1-2) + n_(3-4) )
     *    + V( 1->3 + 3->1 + 2->4 + 4->2)
     *
     * I don't know yet how this is done and will come back once the rest is
     * finished.
     */
    // dummy behaviour: copy from DenseED and overwrite QC state
    // this is black magic and should be removed ASAP

    // obtain gdstate
    auto gd { DenseED(U,V).gdstate() };

    // obtain data to write to
    auto store { rig->bad() };

    // obtain transform mapping
    /* new state is no longer for
     *     I↓ I↑ B↓ B↑
     * but for
     *   A I↓ B↓ I↑ B↑
     * A (ancillary) is ↓
     */
    static std::map<int,int> transform;
    static bool ini = true;
    if (ini)
    {
        ini = false;
        for (int i{ 0 }; i<16; ++i)
        {
            /* new mask has:
             * 0 unset
             * 1 (I↓) set if 0 is set
             * 2 (B↓) set if 2 is set
             * 3 (I↑) set if 1 is set
             * 4 (B↑) set if 3 is set
             *
             * -> switch 1,2 then shift one left
             */
            int j { (i & ~6) | ((i&4) >> 1) | ((i&2) << 1) };
            j <<= 1;
            transform[i] = j;
        }
    }

    // do the roar
    for (auto m{transform.begin()};m!=transform.end();++m)
    {
        store[m->second] = gd(m->first);
        store[m->second|1] = 0.0;
    }
    return *this;
}

Fourier::spec_t Qmeth::part
                (
                    QC::unitary* first, QC::unitary* second,
                    double step, int counts
                )
{
    /* The full greensfunction is
     *
     * -i < c(t)c^+(0) > -i < c^+(0)c(t) >
     *
     *  plugging in c = P = (X+iY)/2 , c^+ = M = (X-iY)/2 and
     *  c(t) = U^+cU
     *  we get eight summands of the form of <U^+ P U S>
     *   ( or <S U^+ P U> which is the conjugate )
     *  where P,S are either of X,Y. These are computed here
     */
    Fourier::spec_t ret(counts);

    prepare();
    rig->gate(0,QC::H).gate(1,first,0,false);

    QC::Stash stash(*rig);
    for (int i{ 0 }; i<counts; ++i)
    {
        trotterstep(step);
        stash.save();
        rig->gate(1,second,0,true).gate(0,QC::H);
        double u,d;   complex r;
        rig->probZ(0,u,d);   r  = d-u;
        rig->probY(0,u,d);   r += IU*(d-u);
         /* the greens function only need real part
          * so we might as well only compute it (?)
          * just compute it anyways
          */
        ret[i] = r;
        stash.apply();
    }
    return ret;
}
