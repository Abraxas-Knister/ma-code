#include "../src/config.hpp"

#include "../src/twosite.hpp"
#include "../src/dense-ed.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

int main ()
{
    // GREENS FUNCTION -> quantum device??
    double U=1.0,V=0.01;
    Twosite calc{};
    DenseED* diagonalizer = new DenseED(U,V);
    calc.setup = diagonalizer;

    double step = 5e-3;
    calc.compute(step);

    std::vector<double> vv; double oldV=V*10;
    int maxct = 500, ct = 0;
    while ( (++ct < maxct ) && !areNear(V,oldV,1e-7)) // CHECK CONVERGENCE
    {
        oldV = V;

        calc.ckparams(V);     // GET SELF ENERGY -> PARAMETERS (SELF CONSISTENCY)
        diagonalizer->set(U,V);          // UPDATE HAMILTONIAN AND REDO
        step = calc.timestep(); // UPDATE TIMESTEP
        calc.compute(step);

        vv.push_back(V);
    }
    std::cerr << (ct==maxct ? "Warn: many cycles\n" : "");

    delete diagonalizer;
    calc.setup = 0;

    std::ofstream fG("data/mat-gf");
    fG << std::setprecision(15) << *calc.greensfunction;

    std::ofstream vvec("data/mat-converg");
    vvec << std::setprecision(15);
    for (auto i:vv) vvec << i <<'\n';

    return 0;
}
