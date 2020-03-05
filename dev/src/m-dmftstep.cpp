#include "greensfunction.hpp" 
#include <cmath>
#include <iostream> 

double prepare(int, int, m_gf *);
void m_gf::iterate()
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
    const double self0_m2 {prepare(0,index-2,this)},
           self0_m1 {prepare(0,index-1,this)},
           self0_p1 {prepare(0,index+1,this)},
           self0_p2 {prepare(0,index+2,this)},
           self1_m2 {prepare(1,index-2,this)},
           self1_m1 {prepare(1,index-1,this)},
           self1_p1 {prepare(1,index+1,this)},
           self1_p2 {prepare(1,index+2,this)};
    const double dself0_m {self0_m1 - self0_m2},
           dself0_p {self0_p2 - self0_p1},
           dself1_m {self1_m1 - self1_m2},
           dself1_p {self1_p2 - self1_p1};
    const double dself0 {(dself0_p+dself0_p)*0.5},
           dself1 {(dself1_p+dself1_p)*0.5};
    double newV { 1.0/(1.0 - (dself0+dself0)*0.5/dw)};
    static int huhct = 0;
    if (newV<0) { std::cerr << "huh? " << ++huhct << '\n'; }
    newV = sqrt(std::fabs(newV));
    setup->update(setup->U, newV);
}

double prepare(int orb, int i, m_gf *G)
{
    switch (orb){
        case 0:
            return G->freq[i] + G->setup->U/2 - (G->setup->V*G->setup->V)/G->freq[i] - 1.0/G->freqdep0[i].real();
        case 1:
            return G->freq[i] + G->setup->U/2 - (G->setup->V*G->setup->V)/G->freq[i] - 1.0/G->freqdep1[i].real();
    }
}
