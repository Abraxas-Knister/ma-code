#include "config.hpp"

#include "green.hpp"
#include "setup.hpp"

#include <fstream>
#include <iomanip>
#include <vector>

int main ()
{
    // GREENS FUNCTION -> quantum device??
    double U=1.0,V=1e4;
    double oldV=V*10;
    Setup s(U,V);
    green G(s);
    G.compute();

    std::vector<double> vv;
    while (!areNear(V,oldV,1e-6)) // CHECK CONVERGENCE
    {
        oldV = V;

        G.ckparams(U,V); // GET SELF ENERGY GET PARAMETERS (SELF CONSISTENCY)
        s.set(U,V); // UPDATE HAMILTONIAN AND REDO
        G.compute();

        vv.push_back(V);
    }
    std::ofstream fG("data/mat-gf");
    fG << std::setprecision(15) << G;
    std::ofstream vvec("data/mat-converg");
    vvec << std::setprecision(15);
    for (auto i:vv) vvec << i <<'\n';
    return 0;
}
