#include "../src/qc.hpp"
#include "../src/gates.hpp"

#include <iostream>

using namespace QC;

int main()
{
    std::cerr << "A quantum rig with three qbits:\n";
    Rig r(3);
    std::cerr << r 
        << "Standard state is all down ( 1 for ddd, else 0 ).\n"
    ;

    std::cerr << "Acting on the first:\n\n"
        << "Operator X:\n"  << r.gate(0,X) << '\n'
        << "Operator Y:\n"  << r.gate(0,Y) << '\n'
        << "Operator Z:\n"  << r.gate(0,Z) << '\n'
        << "Operator H:\n"  << r.gate(0,H) << '\n'
    ;

    std::cerr << "HZYX = -iHZZ = -iH\n"
        << "so the state should now be -i|+>\n"
        << "and normalising should be possible by XYZH = iH\n"
        << r.gate(0,H).gate(0,Z).gate(0,Y).gate(0,X)
    ;

    std::cerr << "\nActing with creators and annihilators:\n";
    std::cerr << "creating 2-0-1, then destroying 0-1:\n"
        << (((((r + 2) + 0) + 1) - 0) - 1)
        << "Should now be -udd. Destroying the last set:\n"
        << r - 2
        << "Should be -ddd. Destroying 2:\n" << r - 2
        << "Should be 0, creating 2:\n" << r + 2
        << "creating 2:\n" << r + 2
    ;

    std::cerr << "\nTrying the bounds checking: -2 to 6:\n";
    for (int i=-2; i<=6; ++i)
    {
        try { r.gate(i,X); throw 0; }
        catch(int) { std::cerr << "Legal index  : " << i << '\n'; }
        catch(...) { std::cerr << "Illegal index: " << i << '\n'; }
    }

    int ctrl = 0;
    std::cerr << "\nTwo qbit Operators:\n";
    std::cerr
        << "state ddd, CZ(ctrl = 0, on = 1):\n" << r.set(0).gate(1,Z,ctrl)
        << "state dud, CZ(ctrl = 0, on = 1):\n" << r.set(2).gate(1,Z,ctrl)
        << "state ddu, CZ(ctrl = 0, on = 1):\n" << r.set(1).gate(1,Z,ctrl)
        << "state duu, CZ(ctrl = 0, on = 1):\n" << r.set(3).gate(1,Z,ctrl)
        << "controlled phase-shift (ctrl = 0, on = 1) on the result:\n"
        << "rotating by pi:\n"    << r.gate(1,R(1.0),ctrl)
        << "rotating by 1/3pi:\n" << r.gate(1,R(1.0/3.0),ctrl)
        << "rotating by 1/3pi:\n" << r.gate(1,R(1.0/3.0),ctrl)
        << "rotating by 1/3pi:\n" << r.gate(1,R(1.0/3.0),ctrl)
    ;

    std::cerr << "\nRotations:ddu, pi*2/3, on 0\n";
    double mul = 2.0/3.0;
    std::cerr
        << "X:\n" << r.set(1).gate(0,X,mul)
        << "Y:\n" << r.set(1).gate(0,Y,mul)
        << "Z:\n" << r.set(1).gate(0,Z,mul)
    ;

    return 0;
}


