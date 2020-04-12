#ifndef GATES_HPP
#define GATES_HPP
#include "config.hpp"

#include "qc.hpp"

namespace QC
{
    std::function<unitary> R(double);
}

// creator/annihilator
QC::Rig& operator+ (QC::Rig&,int);
QC::Rig& operator- (QC::Rig&,int);

#endif // guard
