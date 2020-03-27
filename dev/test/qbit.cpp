#include "../src/qbit.hpp" 

#include <iomanip> 
#include <iostream>

using namespace QC;

int main()
{
    std::cerr << std::setprecision(3) << std::showpos;
    std::cerr << "Some Qbits:\n";
    {
        std::cerr << "1,1: "  <<   Qbit{1,1}   << '\n';
        std::cerr << "1,-1: " <<   Qbit{1,-1}  << '\n';
        std::cerr << "0,1: "  <<   Qbit{0,1}   << '\n';
        std::cerr << "-1,1: " <<   Qbit{-1,1}  << '\n';
        std::cerr << "0,0: "  <<   Qbit{0,0}   << '\n';
    }

    std::cerr << "Applying some Operators to: ";

    Qbit q(1,0);
    std::cerr << q << '\n';

    std::cerr << "X: ";
    std::cerr << q.X() << '\n';

    std::cerr << "Y: ";
    std::cerr << q.Y() << '\n';

    std::cerr << "Z: ";
    std::cerr << q.Z() << '\n';

    std::cerr << "H: ";
    std::cerr << q.H() << '\n';

    q = Qbit(1,0);
    std::cerr << "first X, then Z: "
        << q.X().Z();

    std::cerr << std::endl;
    return 0;
}
