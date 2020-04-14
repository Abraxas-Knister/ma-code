#ifndef GATES_HPP
#define GATES_HPP
#include "config.hpp"

#include "qc.hpp"

namespace QC
{
    std::function<unitary> R(double);
    std::function<unitary> R(double,double,double);
    std::function<unitary> disturb(double);
    void XX(Rig&,int,int,double);
    void YY(Rig&,int,int,double);
    void ZZ(Rig&,int,int,double);
}

// creator/annihilator
QC::Rig& operator+ (QC::Rig&,int);
QC::Rig& operator- (QC::Rig&,int);

#endif // guard
