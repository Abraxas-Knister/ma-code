// the set function is easy
void Qmeth::set(const double newU, const double newV)
{
    U = newU;
    V = newV;
}

//
Fourier::spec_t Qmeth::green(double step,int counts)
{
    Fourier::spec_t tmp(counts);
    for (int i=0; i<counts; ++i)
          tmp[i]=full(step,i);
    return tmp;
}
