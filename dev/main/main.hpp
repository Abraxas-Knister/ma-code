#include "config.hpp"
#include "greensfunction.hpp"
#include "m-setup.hpp"
#include <iomanip>
#include <iostream>

int main ()
{
// GREENS FUNCTION -> quantum device??
    Setup s(1,1);
    m_gf G(s);
    G.compute();
    std::cout << std::setprecision(15);
    std::cout << G;
// GET SELF ENERGY
// GET PARAMETERS (SELF CONSISTENCY)
// CHECK CONVERGENCE
// UPDATE HAMILTONIAN AND REDO
    return 0;
}
