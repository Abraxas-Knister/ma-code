#include "../src/config.hpp"

#include "../src/dense-ed.hpp"
#include "../src/twosite.hpp"
#include "../src/qmeth.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

void write(const std::string &name, const Twosite& calc, std::vector<double>* Vs=nullptr)
{
    {
        std::ofstream f("data/" + name + "-gf");
        f << std::setprecision(15) << *calc.greensfunction;
    }
    if (Vs)
    {
        std::ofstream f("data/" + name + "-converg");
        f << std::setprecision(15);
        for (auto i : *Vs) f << i <<'\n';
    }
}

int main ()
{

    // calc is the calculator that operates in the mode diagonalizer
    Twosite calc{};
    Setup* diagonalizer = new DenseED(1.0 , 0.01);

    // invocation of the calculator
    std::vector<double> vv;
    converge(&vv,calc,diagonalizer,1e-3,10000);

    // mode is now no longer needed
    delete diagonalizer;

    /* the result of the calculation is stored in the calc
     * and the calculation method can store the convergence
     * of the parameters
     */
    write("mat",calc,&vv);
    vv.clear();

    return 0;
}
