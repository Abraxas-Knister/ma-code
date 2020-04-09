#include "../src/config.hpp"

#include "../src/green.hpp"
#include "../src/setup.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

int main ()
{
    // GREENS FUNCTION -> quantum device??
    double U=1.0,V=0.01;
    Setup s(U,V);
    green G(s);

    double step = 5e-3;
    G.compute(step);

    std::vector<double> vv; double oldV=V*10;
    int maxct = 500, ct = 0;
    while ( (++ct < maxct ) && !areNear(V,oldV,1e-7)) // CHECK CONVERGENCE
    {
        oldV = V;

        G.ckparams(U,V);     // GET SELF ENERGY -> PARAMETERS (SELF CONSISTENCY)
        s.set(U,V);          // UPDATE HAMILTONIAN AND REDO
        step = G.timestep(); // UPDATE TIMESTEP
        G.compute(step);

        vv.push_back(V);
    }
    std::cerr << (ct==maxct ? "Warn: many cycles\n" : "");

    std::ofstream fG("data/mat-gf");
    fG << std::setprecision(15) << G;

    std::ofstream vvec("data/mat-converg");
    vvec << std::setprecision(15);
    for (auto i:vv) vvec << i <<'\n';

    return 0;
}
