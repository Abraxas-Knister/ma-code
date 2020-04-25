#include "../src/qc-stash.hpp"

#include <iostream>

using namespace QC;

int main()
{
    Rig r(3);
    std::cerr << r.gate(1,X) << '\n';
    Stash s(r);
    std::cerr << r.gate(1,X) << '\n';
    int ct=100;
    while (--ct) { s.save(); s.apply(); }
    std::cerr << r << '\n';
}
