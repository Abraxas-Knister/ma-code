double selfenergy(int,const green&);
void green::ckparams(double &V) const
{
    // Want d/dw Re(S) | w=0
    /* That's hopefully the same as
     *
     *  real(
     *    Self(freqdep[1]) - Self(freqdep[0])
     *   ) / ( freq[0] )
     *
     * since freqdep and freq store the positive freqs first
     *
     * Need to calculate Self energy at freq[2] and freq[1] since freq[0] is 0
     * to avoid devide by 0.
     */
    const double dw { gf->valsFreq()[1] };
    const double
        self_1 {selfenergy(1,*this)},
        self_2 {selfenergy(2,*this)};
    const double
        dself {self_2 - self_1};
    double newV { 1.0/(1.0 - dself/dw) };
/* DEB */  //  static int huhct = 0;
/* DEB */  //  if (newV<0) { std::cerr << "=== neg mass: " << ++huhct << " ===\n"; }
    V = sqrt(std::fabs(newV));
}

double selfenergy(int i, const green &G)
{
    // G0**-1 = w + mu - V**2 / w
    // S = G0**-1 - G**-1
    double
        w = G.gf->valsFreq()[i] ,
        g = G.gf->specFreq()[i].real();
    return w + G.setup->getU()/2 - (G.setup->getV()*G.setup->getV())/w - 1.0/g;
}

double green::timestep() const
{
    /* find freqency with maximal weight
     * compute a timestep such that
     * this frequency gets some support points
     * return that timestep
     */
    const auto absComp { [] (const complex& a, const complex& b) -> bool
        { return std::norm(a) < std::norm(b); }
    };
    const auto& f{gf->specFreq()};
    auto max { std::max_element(f.begin(), f.begin() + f.size()/2 , absComp) };
    const auto maxIndex { std::distance(f.begin(),max) };
    const double freq { gf->valsFreq()[maxIndex] };
    return 1.0/(200*freq);
}
