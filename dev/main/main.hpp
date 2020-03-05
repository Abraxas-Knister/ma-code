#include "config.hpp"

#include "greensfunction.hpp"
#include "m-setup.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

int main ()
{
// GREENS FUNCTION -> quantum device??
    Setup s(1,1e4);
    m_gf G(s);
    G.compute();
// GET SELF ENERGY
// GET PARAMETERS (SELF CONSISTENCY)
// CHECK CONVERGENCE
// UPDATE HAMILTONIAN AND REDO
    double oldV = s.V*10;
    std::vector<double> vs;
    while (!areNear(s.V,oldV))
    {
        oldV = s.V;
        vs.push_back(oldV);
        G.iterate();
    }
    vs.push_back(oldV);
    std::cout << std::setprecision(15);
    std::cout << G;
    std::ofstream f("vs",std::ofstream::out);
    f << std::setprecision(15);
    for (int i=0;i<vs.size(); i++)
    {
        f << vs[i] << '\n';
    }
    f.close(); 
    std::cout << G;
    return 0;
}
