#include "config.hpp"

#include "green.hpp"
#include "setup.hpp"

#include <fstream>
#include <iomanip>
#include <iostream> 
#include <vector>

int main ()
{
    // GREENS FUNCTION -> quantum device??
    double U=1.0,V=0.01;
    double oldV=V*10;
    Setup s(U,V);
    green G(s);
    double step = 5e-8; int count = 1000000;
    G.compute(step,count);

    std::vector<double> vv;
    while (!areNear(V,oldV,1e-5)) // CHECK CONVERGENCE
    {
        oldV = V;

        G.ckparams(U,V); // GET SELF ENERGY GET PARAMETERS (SELF CONSISTENCY)
        s.set(U,V); // UPDATE HAMILTONIAN AND REDO
        G.compute(step,count);

        vv.push_back(V);
    }
    std::ofstream fG("data/mat-gf");
    fG << std::setprecision(15) << G;
    std::ofstream vvec("data/mat-converg");
    vvec << std::setprecision(15);
    for (auto i:vv) vvec << i <<'\n';
    return 0;
}
