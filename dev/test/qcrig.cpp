#include "../src/qc.hpp"

#include <iostream>

using namespace QC;

int main()
{
    std::cerr << "A quantum rig with four qbits:\n";
    Rig r(4);
    std::cerr << r 
        << "Standard state is all down ( 1 for dddd, else 0 ).\n";

    std::cerr << "Acting on the first:\n\n"
        << "Operator X:\n"  << r.X(0) << '\n'
        << "Operator Y:\n"  << r.Y(0) << '\n'
        << "Operator Z:\n"  << r.Z(0) << '\n'
        << "Operator H:\n"  << r.H(0) << '\n';

    std::cerr << "HZYX = -iHZZ = -iH\n"
        << "so the state should now be -i|+>\n"
        << "and normalising should be possible by XYZH = iH\n"
        << r.H(0).Z(0).Y(0).X(0);

    std::cerr << "\nActing with creators and annihilators:\n";
    std::cerr << "creating 2-0-1, then destroying 0-1:\n"
        << r.C(2).C(0).C(1).A(0).A(1)
        << "Should now be -dudd. Destroying the last set:\n"
        << r.A(2)
        << "Should be -dddd. Destroying 3:\n" << r.A(3)
        << "Should be 0, creating 2:\n" << r.C(2)
        << "creating 2:\n" << r.C(2);

    std::cerr << "\nTrying the bounds checking: -2 to 6:\n";
    for (int i=-2; i<=6; ++i)
    {
        try { r.X(i); throw 0; }
        catch(int) { std::cerr << "Legal index  : " << i << '\n'; }
        catch(...) { std::cerr << "Illegal index: " << i << '\n'; }
    }

    std::cerr << "\nTwo qbit Operators:\n";
    std::cerr
        << "state dddd, CZ(ctrl = 0, on = 1):\n" << r.set(0).CZ(1,0)
        << "state ddud, CZ(ctrl = 0, on = 1):\n" << r.set(2).CZ(1,0)
        << "state dddu, CZ(ctrl = 0, on = 1):\n" << r.set(1).CZ(1,0)
        << "state dduu, CZ(ctrl = 0, on = 1):\n" << r.set(3).CZ(1,0)
        << "rotating by pi:\n" << r.CR(1,1.0,0)
        << "rotating by 1/3pi:\n" << r.CR(1,1.0/3.0,0)
        << "rotating by 1/3pi:\n" << r.CR(1,1.0/3.0,0)
        << "rotating by 1/3pi:\n" << r.CR(1,1.0/3.0,0)
    ;
    return 0;
}


