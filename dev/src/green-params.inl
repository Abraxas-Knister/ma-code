double selfenergy(int,const green *);
void green::ckparams(double &U , double &V) const
{
    // Plan: go through freq until it's rougly 0
    // then pick two points before and after
    //      (ie no ... no yes yes 0 yes yes no ... no)
    // and compute the self energy at these points.
    // then take the difference and the mean of these values.
    // (do this for the real part only)
    // -> thats d/dw Re(S) | w=0
    int index=0;
    while ( !areNear(freq[index]) ) index++;
    const double dw {freq[1]-freq[0]};
    const double
        self_m2 {selfenergy(index-2,this)},
        self_m1 {selfenergy(index-1,this)},
        self_p1 {selfenergy(index+1,this)},
        self_p2 {selfenergy(index+2,this)};
    const double
        dself_m {self_m1 - self_m2},
        dself_p {self_p2 - self_p1};
    const double dself { (dself_p + dself_m)*0.5 };
    double newV { 1.0/(1.0 - dself/dw) };
    /*
/ *DEB* /    static int huhct = 0;
/ *DEB* /    if (newV<0) { std::cerr << "=== neg mass: " << ++huhct << " ===\n"; }
*/
    V = sqrt(std::fabs(newV));
    U = setup.U;
}

double selfenergy(int i, const green *G)
{
    // G0**-1 = w + mu - V**2 / w
    // S = G0**-1 - G**-1
    return G->freq[i] + G->setup.U/2 - (G->setup.V*G->setup.V)/G->freq[i] - 1.0/G->freqdep[i].real();
}
