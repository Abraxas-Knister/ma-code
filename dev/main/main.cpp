#include "../src/config.hpp"

#include "../src/twosite.hpp"
#include "../src/dense-ed.hpp"

#include <fstream>
#include <iomanip>
#include <vector>

int main ()
{
    // calc is the calculator that operates in the mode diagonalizer
    Twosite calc{};
    Setup* diagonalizer = new DenseED(1.0 , 0.01);

    // invocation of the calculator
    std::vector<double> vv;
    converge(&vv,calc,diagonalizer,1e-7);

    // mode is now no longer needed
    delete diagonalizer;

    // the result of the calculation is stored in the calc
    std::ofstream fG("data/mat-gf");
    fG << std::setprecision(15) << *calc.greensfunction;

    // the calculation routine can store the history of the parameter
    std::ofstream vvec("data/mat-converg");
    vvec << std::setprecision(15);
    for (auto i:vv) vvec << i <<'\n';

    return 0;
}
