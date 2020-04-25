// the set function is easy
void Qmeth::set(const double newU, const double newV)
{
    U = newU;
    V = newV;
}

//
Fourier::spec_t Qmeth::green(double step,int counts)
{
    /*  summands of c(t)c^+(0)
     *  +   1/4   U^+ X U X =: XX
     *  -   i/4   U^+ X U Y =: XY
     *  +   i/4   U^+ Y U X =: YX
     *  +   1/4   U^+ Y U Y =: YY
     *
     *  summands of c^+(0)c(t)
     *  +   1/4   X U^+ X U  is  conj(XX)
     *  +   i/4   X U^+ Y U  is  conj(YX) *  i
     *  -   i/4   Y U^+ X U  is  conj(XY) * -i
     *  +   1/4   Y U^+ Y U  is  conj(YY)
     *
     *  total:
     *  XX + conj(XX) -i XY -i conj(XY) + i YX + i conj(YX) + YY + conj(YY)
     *  = ( (re(XX) + re(YY)) + i (re(YX) - re(XY)) )/2
     *
     *  then multiply by -i
     */
    Fourier::spec_t
        XX = part(QC::X,QC::X,step,counts),
        XY = part(QC::X,QC::Y,step,counts),
        YX = part(QC::Y,QC::X,step,counts),
        YY = part(QC::Y,QC::Y,step,counts),
        tmp;
    for (int i{ 0 }; i<XX.size(); ++i)
          tmp.push_back(
             -IU*0.5*(XX[i] + YY[i]).real()
             +   0.5*(YX[i] - XY[i]).real()
          );
    return tmp;
}
