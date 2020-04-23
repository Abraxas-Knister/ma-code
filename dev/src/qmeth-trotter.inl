Qmeth& Qmeth::trotterstep(double step)
{
    /* Last four qbits in the rig correspond to
     * 
     *    ↓i ↓b ↑i ↑b
     *     1  2  3  4
     *
     * the Hamiltonian is 
     * U( n_up * n_dw )_i - mu (n_up + n_dw)_i + V(...)
     * where the _i refers to the impurity. 
     * 
     * In Jordan Wigner n = 1/2 ( 1 - Z )
     * -> n_up * n_dw = 1/4 ( 1 - Z_3 ) (1 - Z_1 )
     *  = 1/4 ( 1 - Z_1 - Z_3 + Z_1*Z_3 )
     *  mu = U/2 so the "U times ... " term reduces to
     *  U/4 Z_3*Z_1 if we neglect additive constants 
     *  (-> incorrect phase in end result -> doesn't matter)
     *
     * V term:
     *  V( c^+_1 c_2 + c^+_2c_1 
     *     + 1->3,2->4 )
     *
     *  with jordan wigner: ZP = P, MZ = M so 
     *  M_2 Z_1 P_1 = M_2 P_1 and
     *  M_1 P_2 Z_1 = M_1 P_2
     *  both added = 2 ( X_1X_2 + Y_1Y_2 )
     *
     *  same for 01->23, so total:
     *
     *  V/2 ( X_1X_2 + X_3X_4 
     *     +  X->Y )
     */
    QC::XX(*rig,1,2,-V/2.0*step);
    QC::XX(*rig,3,4,-V/2.0*step);
    QC::YY(*rig,1,2,-V/2.0*step);
    QC::YY(*rig,3,4,-V/2.0*step);
    QC::ZZ(*rig,1,3,-U/4.0*step);
    return *this;
}

Qmeth& Qmeth::evolve(double step,int counts)
{
    do
          trotterstep(step);
    while (--counts);
    return *this;
}
