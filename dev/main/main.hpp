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
    double U=1.0,V=1e4;
    double oldV=V*10;
    Setup s(U,V);
    green G(s);
    G.compute();
// GET SELF ENERGY
// GET PARAMETERS (SELF CONSISTENCY)
// CHECK CONVERGENCE
// UPDATE HAMILTONIAN AND REDO
    std::vector<double> vv;
    while (!areNear(V,oldV,1e-5))
    {
        oldV = V;

        G.ckparams(U,V);
        s.set(U,V);
        G.compute();

        vv.push_back(V);
    }
    std::cout << std::setprecision(15);
    std::cout << G;
    std::cerr << std::setprecision(15);
    for (auto i:vv) std::cerr << i <<'\n';
    return 0;
}
