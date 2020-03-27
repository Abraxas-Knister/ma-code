#include "../src/qc.hpp"

#include <iostream>

using namespace QC;

int main()
{
    std::cerr << "A quantum rig with four qbits:\n";
    Rig r(4);
    for (int i=0; i<r.size(); ++i)
          std::cerr << r.get(i) << ' ';
    std::cerr << '\n';
    std::cerr << "Standard state is all down ( 1 , 0).\n";

    std::cerr << "Acted on by a creation operator (bit 1):\n";
    r.JWC(0);
    for (int i=0; i<r.size(); ++i)
          std::cerr << r.get(i) << ' ';
    std::cerr << '\n';

    std::cerr << "Acted on by an annihilation operator (bit 1):\n";
    r.JWA(0);
    for (int i=0; i<r.size(); ++i)
          std::cerr << r.get(i) << ' ';
    std::cerr << '\n';

    std::cerr << "Acted on by a creation operator (bit 3):\n";
    r.JWC(2);
    for (int i=0; i<r.size(); ++i)
          std::cerr << r.get(i) << ' ';
    std::cerr << '\n';
    
    std::cerr << "Acted on by an annihilation operator (bit 3):\n";
    r.JWA(2);
    for (int i=0; i<r.size(); ++i)
          std::cerr << r.get(i) << ' ';
    std::cerr << "\n\n";

    std::cerr << "first create 1, then 2, then 3, then annihilate 2:\n";
    r.JWC(0).JWC(1).JWC(2).JWA(1);
    for (int i=0; i<r.size(); ++i)
          std::cerr << r.get(i) << ' ';
    std::cerr << '\n';

    std::cerr << "Acting with on an illegal index: -1\n";
    r.X(-1);
    return 0;
}


